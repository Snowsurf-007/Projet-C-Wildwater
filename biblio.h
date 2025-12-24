#ifndef BIBLIO_H
#define BIBLIO_H

/* =====================
      BIBLIOTHEQUES
   ===================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define TAILLEID 100

/* =====================
        STRUCTURES
   ===================== */
typedef struct AVL {
    struct Arbre* arbre;
    int equil;
    double elmt;
    double max;
    float real;
    float src;
    char* ID;
    struct AVL* fg;
    struct AVL* fd;
} AVL;

typedef struct Arbre {
    struct Chainon* enfants;
    double elmt;
    double litre;
    int nb_enfants;
    char* ID;
} Arbre;

typedef struct File {
    struct Chainon* head;
    struct Chainon* tail;
} File;

typedef struct Chainon {
    struct Arbre* enfant;
    struct Chainon* next;
} Chainon;

/* =====================
         FONCTIONS
   ===================== */

// Utilitaires
int max(int a, int b);
int min(int a, int b);
int hauteur(AVL* a);
int equilibre(AVL* a);
int recherche(AVL* a, char* e);
AVL* rechercherAVL(AVL* a, char* id);

// Rotations et équilibrage
AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);
AVL* equilibrage(AVL* a);

// Création et insertion
AVL* creationAVL(int e, char* c);
AVL* creationRealAVL(float max, float real, float src, char* c);
AVL* creationStrAVL(Arbre* e, char* c);
AVL* insertAVL(AVL* a, char* e, int* h, int capter);
AVL* insertRealAVL(AVL* a, char* e, int* h, float max, float real, float src);
AVL* insertStrAVL(AVL* a, char* e, int* h, Arbre* p);
AVL* insert_enfant(AVL* a, char* e, int* h, Arbre* enfant);
Chainon* creationChainon(Arbre* bebe);
Chainon* empiler(Chainon* pliste, Arbre* bebe);
Arbre* insert(char* id, int nb);
AVL* get_or_create(AVL* avl, char* id, int* h, Arbre** res);
Arbre* mega_arbre(FILE* US, FILE* SJ, FILE* JR, FILE* RU);

// Affichage et traitement
void traiter(AVL* a);
void traiterReal(AVL* a);
void infixe(AVL* a);
void infixeReal(AVL* a);
void prefixe(AVL* a);
void suffixe(AVL* a);
void afficherABR(Arbre* a, int niveau);
void afficherAVL(AVL* a);

// Fichiers
void ecrire(FILE* f, AVL* usine);
void ecrireReal(FILE* f, AVL* usine);

// Libération mémoire
void libererAVL(AVL* a);
void libererArbre(Arbre* a);

void calcul(Arbre* a, double* somme_fuites);
float source(FILE* f);

void mode1(char* inputFile, char* outputFile);
void mode2(char* inputFile, char* outputFile);
void mode3(char* maxFile, char* realFile, char* srcFile, char* outputFile);
void mode4(char* suFile, char* usFile, char* sjFile, char* jrFile, char* ruFile);

int main(int argc, char* argv[]);



#endif // BIBLIO_H
