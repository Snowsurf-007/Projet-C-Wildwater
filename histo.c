#include "biblio.h"

/* =====================
   FONCTIONS UTILITAIRES
   ===================== */
int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int hauteur(AVL* a) {
    if(a == NULL) return -1;
    return 1 + max(hauteur(a->fg), hauteur(a->fd));
}

int equilibre(AVL* a) {
    if(a == NULL) return 0;
    return hauteur(a->fd) - hauteur(a->fg);
}

int recherche(AVL* a, char* e) {
    if(a == NULL) return 1;
    int z = strcmp(a->ID, e);
    if(z == 0) return 0;
    else if(z > 0) return recherche(a->fg, e);
    else return recherche(a->fd, e);
}

/* =====================
   ROTATIONS
   ===================== */
AVL* rotationGauche(AVL* a) {
    AVL* p = a->fd;
    a->fd = p->fg;
    p->fg = a;
    a->equil = equilibre(a);
    p->equil = equilibre(p);
    return p;
}

AVL* rotationDroite(AVL* a) {
    AVL* p = a->fg;
    a->fg = p->fd;
    p->fd = a;
    a->equil = equilibre(a);
    p->equil = equilibre(p);
    return p;
}

AVL* doubleRotationGauche(AVL* a) {
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

AVL* doubleRotationDroite(AVL* a) {
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

AVL* equilibrage(AVL* a) {
    a->equil = equilibre(a);
    if(a->equil == 2) {
        if(a->fd->equil < 0)
            return doubleRotationGauche(a);
        else
            return rotationGauche(a);
    }
    else if(a->equil == -2) {
        if(a->fg->equil > 0)
            return doubleRotationDroite(a);
        else
            return rotationDroite(a);
    }
    return a;
}

/* =====================
   CRÉATION DE NŒUDS
   ===================== */
AVL* creationAVL(int e, char* c) {
    AVL* newNode = malloc(sizeof(AVL));
    if(!newNode) {
        printf("Erreur : malloc\n");
        exit(1);
    }
    newNode->elmt = e;
    newNode->max = 0;
    newNode->real = 0;
    newNode->src = 0;
    newNode->fg = NULL;
    newNode->fd = NULL;
    newNode->equil = 0;
    newNode->ID = strdup(c);
    return newNode;
}

AVL* creationRealAVL(float max, float real, float src, char* c) {
    AVL* newNode = malloc(sizeof(AVL));
    if(!newNode) {
        printf("Erreur : malloc\n");
        exit(1);
    }
    newNode->elmt = 0;
    newNode->max = max;
    newNode->real = real;
    newNode->src = src;
    newNode->fg = NULL;
    newNode->fd = NULL;
    newNode->equil = 0;
    newNode->ID = strdup(c);
    return newNode;
}

/* =====================
   INSERTION
   ===================== */
AVL* insertAVL(AVL* a, char* e, int* h, int capter) {
    if (a == NULL) {
        *h = 1;
        return creationAVL(capter, e);
    }
    int z = strcmp(a->ID, e);
    if (z == 0) {
        a->elmt = a->elmt + capter;
        return a;
    }
    else if (z > 0) {
        a->fg = insertAVL(a->fg, e, h, capter);
        *h = -*h;
    }
    else if(z < 0) {
        a->fd = insertAVL(a->fd, e, h, capter);
    }
    else {
        *h = 0;
        return a;
    }
    if(*h != 0) {
        a->equil = a->equil + *h;
        a = equilibrage(a);
        if(a->equil == 0) *h = 0;
        else *h = 1;
    }
    return a;
}

AVL* insertRealAVL(AVL* a, char* e, int* h, float max, float real, float src) {
    if (a == NULL) {
        *h = 1;
        return creationRealAVL(max, real, src, e);
    }
    int z = strcmp(a->ID, e);
    if (z == 0) {
        if(max != 0) a->max = a->max + max;
        else if(real != 0) a->real = a->real + real;
        else if(src != 0) a->src = a->src + src;
        return a;
    }
    else if (z > 0) {
        a->fg = insertRealAVL(a->fg, e, h, max, real, src);
        *h = -*h;
    }
    else if(z < 0) {
        a->fd = insertRealAVL(a->fd, e, h, max, real, src);
    }
    else {
        *h = 0;
        return a;
    }
    if(*h != 0) {
        a->equil = a->equil + *h;
        a = equilibrage(a);
        if(a->equil == 0) *h = 0;
        else *h = 1;
    }
    return a;
}

/* =====================
   AFFICHAGE
   ===================== */
void traiter(AVL* a) {
    if(a != NULL)
        printf("%f (%s)  eq=%d\n", a->elmt, a->ID, a->equil);
}

void traiterReal(AVL* a) {
    if(a != NULL)
        printf("max=%f real=%f src=%f (%s)  eq=%d\n", a->max, a->real, a->src, a->ID, a->equil);
}

void infixe(AVL* a) {
    if(a == NULL) return;
    infixe(a->fg);
    traiter(a);
    infixe(a->fd);
}

void infixeReal(AVL* a) {
    if(a == NULL) return;
    infixeReal(a->fg);
    traiterReal(a);
    infixeReal(a->fd);
}

/* =====================
   ÉCRITURE FICHIER
   ===================== */
void ecrire(FILE* f, AVL* usine) {
    if(usine != NULL) {
        ecrire(f, usine->fg);
        fprintf(f, "%s;%f\n", usine->ID, usine->elmt);
        ecrire(f, usine->fd);
    }
}

void ecrireReal(FILE* f, AVL* usine) {
    if(usine != NULL) {
        ecrireReal(f, usine->fg);
        fprintf(f, "%s;%f;%f;%f\n", usine->ID, usine->max, usine->real, usine->src);
        ecrireReal(f, usine->fd);
    }
}

/* =====================
   LIBÉRATION MÉMOIRE
   ===================== */
void libererAVL(AVL* a) {
    if(a == NULL) return;
    libererAVL(a->fg);
    libererAVL(a->fd);
    free(a->ID);
    free(a);
}



void mode1(char* inputFile, char* outputFile) {

    int h = 0;
    FILE* f = fopen(inputFile, "r");
    
    if(f == NULL) {
        printf("Erreur: impossible d'ouvrir %s\n", inputFile);
        exit(45);
    }
    
    FILE* fichier = fopen(outputFile, "w");
    
    if(fichier == NULL) {
        printf("Erreur: impossible de créer %s\n", outputFile);
        fclose(f);
        exit(0);
    }
    
    int a;
    char* ID = malloc(TAILLEID * sizeof(char));
    AVL* usine = NULL;
    
    while (fscanf(f, "%100[^;];%d", ID, &a) == 2) {
        usine = insertAVL(usine, ID, &h, a);
    }
    
    ecrire(fichier, usine);
    
    fclose(fichier);
    fclose(f);
    free(ID);
    libererAVL(usine);
}



void mode2(char* inputFile, char* outputFile) {

    int h = 0;
    FILE* f = fopen(inputFile, "r");
    
    if(f == NULL) {
        printf("Erreur: impossible d'ouvrir %s\n", inputFile);
        exit(45);
    }
    
    FILE* fichier = fopen(outputFile, "w");
    
    if(fichier == NULL) {
        printf("Erreur: impossible de créer %s\n", outputFile);
        fclose(f);
        exit(0);
    }
    
    int a;
    float b, c;
    char* ID = malloc(TAILLEID * sizeof(char));
    AVL* usine = NULL;
    
    while (fscanf(f, "%100[^;];%d;%f", ID, &a, &b) == 3) {
        c = a / 1.0 - (a * (b / 100));
        usine = insertAVL(usine, ID, &h, c);
        c = 0;
    }
    
    ecrire(fichier, usine);
    
    fclose(fichier);
    fclose(f);
    free(ID);
    libererAVL(usine);
}



void mode3(char* maxFile, char* realFile, char* srcFile, char* outputFile) {

    int h = 0;
    
    FILE* fmax = fopen(maxFile, "r");
    FILE* freal = fopen(realFile, "r");
    FILE* fsrc = fopen(srcFile, "r");
    
    if(fmax == NULL || freal == NULL || fsrc == NULL) {
        printf("Erreur: impossible d'ouvrir les fichiers d'entrée\n");
        if(fmax) fclose(fmax);
        if(freal) fclose(freal);
        if(fsrc) fclose(fsrc);
        exit(45);
    }
    
    FILE* fichier = fopen(outputFile, "w");
    
    if(fichier == NULL) {
        printf("Erreur: impossible de créer %s\n", outputFile);
        fclose(fmax);
        fclose(freal);
        fclose(fsrc);
        exit(0);
    }
    
    float a;
    char* ID = malloc(TAILLEID * sizeof(char));
    AVL* usine = NULL;
    
    // Lecture du fichier max
    while (fscanf(fmax, "%100[^;];%f", ID, &a) == 2) {
        usine = insertRealAVL(usine, ID, &h, a, 0, 0);
    }
    
    // Lecture du fichier real
    rewind(freal);
    while (fscanf(freal, "%100[^;];%f", ID, &a) == 2) {
        usine = insertRealAVL(usine, ID, &h, 0, a, 0);
    }
    
    // Lecture du fichier src
    while (fscanf(fsrc, "%100[^;];%f", ID, &a) == 2) {
        usine = insertRealAVL(usine, ID, &h, 0, 0, a);
    }
    
    ecrireReal(fichier, usine);
    
    fclose(fichier);
    fclose(fmax);
    fclose(freal);
    fclose(fsrc);
    free(ID);
    libererAVL(usine);
}



int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage:\n");
        printf("  Mode 1: %s 1 input.csv output.csv\n", argv[0]);
        printf("  Mode 2: %s 2 input.csv output.csv\n", argv[0]);
        printf("  Mode 3: %s 3 max.csv real.csv src.csv output.csv\n", argv[0]);
        return 1;
    }
    
    int mode = atoi(argv[1]);
    
    switch(mode) {
        case 1:
            if(argc != 4) {
                printf("Mode 1 nécessite: %s 1 input.csv output.csv\n", argv[0]);
                return 1;
            }
            mode1(argv[2], argv[3]);
            break;
            
        case 2:
            if(argc != 4) {
                printf("Mode 2 nécessite: %s 2 input.csv output.csv\n", argv[0]);
                return 1;
            }
            mode2(argv[2], argv[3]);
            break;
            
        case 3:
            if(argc != 6) {
                printf("Mode 3 nécessite: %s 3 max.csv real.csv src.csv output.csv\n", argv[0]);
                return 1;
            }
            mode3(argv[2], argv[3], argv[4], argv[5]);
            break;
            
        default:
            printf("Mode invalide. Utilisez 1, 2 ou 3.\n");
            return 1;
    }
    
    return 0;
}
