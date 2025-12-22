#ifndef BIBLIO_H
#define BIBLIO_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define TAILLEID 20



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

int main(int argc, char* argv[]);
int max(int a, int b);
int min(int a, int b);
int hauteur(AVL* a);
int equilibre(AVL* a);
void ecrire(FILE* f, AVL* usine);


void recherche(AVL* a, char* e,Arbre* bebe);
AVL* creationStrAVL(Arbre* e, char* c);
AVL* creationAVL(int e, char* c);

AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);

AVL* equilibrage(AVL* a);

AVL* insertStrAVL(AVL* a, char* e, int* h, Arbre*p);
AVL* insertAVL(AVL* a, char* e,int* h,int capter);


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
Chainon* creationChainon(Arbre* bebe);
Chainon* empiler(Chainon* pliste, Arbre* bebe);


AVL* rechercherAVL(AVL* a, char* id);
AVL* insert_enfant(AVL* a, char* e, int* h, Arbre* enfant);
AVL* get_or_create(AVL* avl, char* id, int* h, Arbre** res);

Arbre* insert(char* id, int nb);

void afficherABR(Arbre* a, int niveau);
void afficherAVL(AVL* a);

Arbre* mega_arbre(FILE* US, FILE* SJ, FILE* JR, FILE* RU);

void calcul(Arbre* a, float* somme);

#endif // BIBLIO_H
