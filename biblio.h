#ifndef BIBLIO_H
#define BIBLIO_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define TAILLEID 20

typedef struct AVL {
	struct Arbre* arbre;
	int equil;
	char* ID;
	struct AVL* fg;
	struct AVL* fd;
} AVL;



typedef struct Arbre {
	struct Chainon* enfants;
	float elmt;
	float litre;
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

int main(int argc, char* argv[]);
int max(int a, int b);
int min(int a, int b);
int hauteur(AVL* a);
int equilibre(AVL* a);

/* ======== Fonctions AVL ======== */
void recherche(AVL* a, char* e,Arbre* bebe);
AVL* creationAVL(Arbre* e, char* c);

AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);

AVL* equilibrage(AVL* a);

AVL* insertStrAVL(AVL* a, char* e, int* h, Arbre*p);

/* ======== Affichage ======== */
void traiter(AVL* a);
void infixe(AVL* a);
void prefixe(AVL* a);
void suffixe(AVL* a);

void test(FILE* f);

Chainon* creationChainon(Arbre* bebe);
Chainon* empiler(Chainon* pliste, Arbre* bebe);
Arbre* creation(char* idav);
Arbre* creation2(char* idam, char* idav, float fuite);
void affichage(Arbre* a,int niveau);
Arbre* mega_arbre(FILE* US, FILE* SJ, FILE* JR, FILE* RU);

#endif // BIBLIO_H
