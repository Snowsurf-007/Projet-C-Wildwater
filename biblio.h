#ifndef BIBLIO_H
#define BIBLIO_H



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
	int  elmt;
	char* ID;
	struct AVL* fg;
	struct AVL* fd;
} AVL;



typedef struct Arbre {
	struct Chainon* enfants;
	float elmt;
	float litre;
	int nb_enfants;
	char*ID;
} Arbre;



typedef struct File{
  struct Chainon* head;
  struct Chainon* tail;
}File;



typedef struct Chainon {
	struct Arbre* enfant;
	struct Chainon* next;
} Chainon;



/* =====================
	PROTOTYPES DES FCTS
   ===================== */
//utilitaire
int max(int a, int b);
int min(int a, int b);
int hauteur(AVL* a);

//creation et insertion
AVL* creationStrAVL(Arbre* e, char* c);
AVL* creationAVL(int e, char* c);
AVL* insertStrAVL(AVL* a, char* e, int* h, Arbre* p);
AVL* insertAVL(AVL* a, char* e,int* h,int capter);

//rotations et equilibre
AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);
int equilibre(AVL* a);
AVL* equilibrage(AVL* a);


//affichage
void traiter(AVL* a);
void infixe(AVL* a);
void prefixe(AVL* a);
void suffixe(AVL* a);



#endif // BIBLIO_H
