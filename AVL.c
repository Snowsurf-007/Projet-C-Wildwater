#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =====================
   UTILS
   ===================== */

int max(int a, int b){
    return (a > b) ? a : b;
}

int min(int a, int b){
    return (a < b) ? a : b;
}

/* =====================
   HAUTEUR / ÉQUILIBRE
   ===================== */

int hauteur(AVL* a){
    if(a == NULL) return -1;
    return 1 + max(hauteur(a->fg), hauteur(a->fd));
}

int equilibre(AVL* a){
    if(a == NULL) return 0;
    return hauteur(a->fd) - hauteur(a->fg);
}

/* =====================
   CRÉATION AVL
   ===================== */

AVL* creationStrAVL(Arbre* e, char* c){
    AVL* n = malloc(sizeof(AVL));
    if(!n){
        perror("malloc");
        exit(1);
    }

    n->arbre = e;
    n->fg = NULL;
    n->fd = NULL;
    n->equil = 0;

    /* COPIE DE L’ID (OBLIGATOIRE) */
    n->ID = malloc(strlen(c) + 1);
    if(!n->ID){
        perror("malloc");
        exit(1);
    }
    strcpy(n->ID, c);

    return n;
}



AVL* creationAVL(int e, char* c){
    AVL* newNode = malloc(sizeof(AVL));
    if(!newNode){
        printf("Erreur : malloc\n");
        exit(1);
    }

    newNode->elmt = e;
    newNode->fg = NULL;
    newNode->fd = NULL;
    newNode->equil = 0;
    newNode->ID = strdup(c);

    return newNode;
}

/* =====================
   ROTATIONS
   ===================== */

AVL* rotationGauche(AVL* a){
    AVL* p = a->fd;

    a->fd = p->fg;
    p->fg = a;

    a->equil = equilibre(a);
    p->equil = equilibre(p);

    return p;
}

AVL* rotationDroite(AVL* a){
    AVL* p = a->fg;

    a->fg = p->fd;
    p->fd = a;

    a->equil = equilibre(a);
    p->equil = equilibre(p);

    return p;
}

AVL* doubleRotationGauche(AVL* a){
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

AVL* doubleRotationDroite(AVL* a){
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

/* =====================
   ÉQUILIBRAGE
   ===================== */

AVL* equilibrage(AVL* a){
    a->equil = equilibre(a);

    if(a->equil == 2){
        if(a->fd->equil < 0)
            return doubleRotationGauche(a);
        else
            return rotationGauche(a);
    }
    else if(a->equil == -2){
        if(a->fg->equil > 0)
            return doubleRotationDroite(a);
        else
            return rotationDroite(a);
    }
    return a;
}

/* =====================
   INSERTION AVL
   ===================== */

AVL* insertStrAVL(AVL* a, char* e, int* h, Arbre* p){

    if(a == NULL){
        *h = 1;
        return creationStrAVL(p, e);
    }

    int z = strcmp(e, a->ID);

    if(z == 0){
        /*  NE JAMAIS ÉCRASER a->arbre */
        *h = 0;
        return a;
    }
    else if(z < 0){
        a->fg = insertStrAVL(a->fg, e, h, p);
        *h = -*h;
    }
    else{
        a->fd = insertStrAVL(a->fd, e, h, p);
    }

    if(*h != 0){
        a = equilibrage(a);
        *h = (a->equil == 0) ? 0 : 1;
    }

    return a;
}



AVL* insertAVL(AVL* a, char* e,int* h,int capter) {
    if (a == NULL) {
    	*h=1;
        return creationAVL(capter, e);
    }

    int z = strcmp(a->ID, e);

    if (z == 0) {
        //printf("Cet élément est déjà présent dans l'AVL\n");
        a->elmt = a->elmt+ capter; 
        return a;
    }
    else if (z > 0) {
        a->fg = insertAVL(a->fg, e, h, capter);
        *h=-*h;
    }
    else if(z < 0){
        a->fd = insertAVL(a->fd, e, h, capter);
    }
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equil=a->equil+*h;
        a=equilibrage(a);
        if(a->equil==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

/* =====================
   AFFICHAGE AVL
   ===================== */

void traiter(AVL* a){
    if(a)
        printf("(%s) eq=%d\n", a->ID, a->equil);
}

void infixe(AVL* a){
    if(a == NULL) return;
    infixe(a->fg);
    traiter(a);
    infixe(a->fd);
}

void prefixe(AVL* a){
    if(a == NULL) return;
    traiter(a);
    prefixe(a->fg);
    prefixe(a->fd);
}

void suffixe(AVL* a){
    if(a == NULL) return;
    suffixe(a->fg);
    suffixe(a->fd);
    traiter(a);
}
