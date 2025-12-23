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
    float elmt;
    float max;
    float real;
    float src;
    char* ID;
    struct AVL* fg;
    struct AVL* fd;
} AVL;

typedef struct Arbre {
    struct Chainon* enfants;
    float elmt;
    float litre;
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

// Rotations et équilibrage
AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);
AVL* equilibrage(AVL* a);

// Création et insertion
AVL* creationAVL(int e, char* c);
AVL* creationRealAVL(float max, float real, float src, char* c);
AVL* insertAVL(AVL* a, char* e, int* h, int capter);
AVL* insertRealAVL(AVL* a, char* e, int* h, float max, float real, float src);

// Affichage et traitement
void traiter(AVL* a);
void traiterReal(AVL* a);
void infixe(AVL* a);
void infixeReal(AVL* a);

// Fichiers
void ecrire(FILE* f, AVL* usine);
void ecrireReal(FILE* f, AVL* usine);

// Libération mémoire
void libererAVL(AVL* a);

#endif // BIBLIO_H
