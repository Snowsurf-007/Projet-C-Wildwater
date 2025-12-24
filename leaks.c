#include "biblio.h"

/* ============================================================
 *  Gestion des listes chaînées d’enfants
 * ============================================================ */

/* Crée un maillon de liste chaînée pointant vers un Arbre */
Chainon* creationChainon(Arbre* bebe) {
    Chainon* chainon = malloc(sizeof(Chainon));
    if (!chainon) exit(66);   // Sécurité allocation

    chainon->enfant = bebe;
    chainon->next = NULL;
    return chainon;
}

/* Empile un enfant dans la liste chaînée */
Chainon* empiler(Chainon* pliste, Arbre* bebe) {
    Chainon* chainon = creationChainon(bebe);
    chainon->next = pliste;
    return chainon;
}

/* ============================================================
 *  Fonctions AVL
 * ============================================================ */

/* Recherche d’un identifiant dans l’AVL */
AVL* rechercherAVL(AVL* a, char* id) {
    if (!a) return NULL;

    int c = strcmp(id, a->ID);
    if (c == 0) return a;
    if (c < 0) return rechercherAVL(a->fg, id);
    return rechercherAVL(a->fd, id);
}

/* Création d’un nœud Arbre */
Arbre* insert(char* id, int nb) {
    Arbre* new = malloc(sizeof(Arbre));
    if (!new) exit(66);

    new->ID = malloc(strlen(id) + 1);
    if (!new->ID) exit(66);

    strcpy(new->ID, id);

    new->elmt = nb;       // Peut être volume OU pourcentage
    new->enfants = NULL;
    new->nb_enfants = 0;
    new->litre = -1;      // Non initialisé
    return new;
}

/* Insère un enfant dans l’AVL */
AVL* insert_enfant(AVL* a, char* e, int* h, Arbre* enfant) {

    if (a == NULL) {
        *h = 1;
        return creationStrAVL(enfant, e);
    }

    int z = strcmp(a->ID, e);

    if (z == 0) {
        /* L’ID existe déjà : on ajoute l’enfant */
        *h = 0;
        a->arbre->enfants = empiler(a->arbre->enfants, enfant);
        return a;
    }
    else if (z > 0) {
        a->fg = insert_enfant(a->fg, e, h, enfant);
        *h = -*h;
    }
    else {
        a->fd = insert_enfant(a->fd, e, h, enfant);
    }

    /* Rééquilibrage AVL */
    if (*h != 0) {
        a = equilibrage(a);
        *h = (a->equil == 0) ? 0 : 1;
    }

    return a;
}

/* Récupère un Arbre existant ou le crée */
AVL* get_or_create(AVL* avl, char* id, int* h, Arbre** res) {

    AVL* n = rechercherAVL(avl, id);

    if (n) {
        *res = n->arbre;
        *h = 0;
        return avl;
    }

    /* Création d’un nouvel Arbre */
    Arbre* a = insert(id, 0);
    avl = insertStrAVL(avl, id, h, a);
    *res = a;

    return avl;
}

/* ============================================================
 *  Libération mémoire
 * ============================================================ */

/* Libère récursivement un Arbre et tous ses enfants */
void libererArbre(Arbre* a)
{
    if (a == NULL)
        return;

    /* Libérer récursivement tous les enfants */
    Chainon* c = a->enfants;
    while (c != NULL) {
        Chainon* tmp = c;
        libererArbre(c->enfant);  // Sous-arbre enfant
        c = c->next;
        free(tmp);                // Maillon de la liste
    }

    /* Libération de l’identifiant */
    free(a->ID);

    /* Libération du nœud */
    free(a);
}

/* Libère uniquement la structure AVL (pas les Arbres) */
void libererAVL(AVL* a) {
    if (a == NULL)
        return;

    libererAVL(a->fg);
    libererAVL(a->fd);

    free(a->ID);   // ID propre à l’AVL
    free(a);       // NE PAS libérer a->arbre
}

/* ============================================================
 *  Construction du méga-arbre
 * ============================================================ */

Arbre* mega_arbre(FILE* US, FILE* SJ, FILE* JR, FILE* RU) {
    char id[TAILLEID];
    char id2[TAILLEID];
    double fuite = 0;
    double max = 0;

    AVL* avl = NULL;
    int h = 0;
    Arbre* parent = NULL;
    Arbre* enfant = NULL;
    Arbre* usine = NULL;

    /* Lecture de la première ligne US : capacité usine */
    if (fscanf(US, "%99[^;];%lf\n", id, &max) != 2)
        return NULL;

    avl = get_or_create(avl, id, &h, &parent);
    parent->elmt = max;
    usine = parent;

    /* Lecture des relations */
    FILE* fichiers[4] = {US, SJ, JR, RU};

    for (int k = 0; k < 4; k++) {
        FILE* f = fichiers[k];
        while (fscanf(f, "%99[^;];%99[^;];%lf\n", id, id2, &fuite) == 3) {

            avl = get_or_create(avl, id, &h, &parent);
            avl = get_or_create(avl, id2, &h, &enfant);

            enfant->elmt = fuite;           // % de fuite
            parent->enfants = empiler(parent->enfants, enfant);
            parent->nb_enfants++;
        }
    }

    /* On peut libérer l’AVL, l’arbre reste valide */
    libererAVL(avl);
    return usine;
}

/* ============================================================
 *  Calcul du volume réellement capté
 * ============================================================ */

float source(FILE* f){
    char source[99];
    char unit[99];
    float volume;
    float pourcentage;
    float res = 0;

    while (fscanf(f,"%99[^;];%99[^;];%f;%f",
                  source, unit, &volume, &pourcentage) == 4) {
        res += volume * (1 - (pourcentage / 10*
