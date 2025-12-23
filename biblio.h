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

//utilitaire
int max(int a, int b);
int min(int a, int b);
int hauteur(AVL* a);

//creation et insertion
AVL* creationStrAVL(Arbre* e, char* c);
AVL* creationAVL(int e, char* c);
AVL* creationRealAVL(float max, float real, float src, char* c);
Chainon* creationChainon(Arbre* bebe);
AVL* insertRealAVL(AVL* a, char* e, int* h, float max, float real, float src);
AVL* insertStrAVL(AVL* a, char* e, int* h, Arbre* p);
AVL* insertAVL(AVL* a, char* e,int* h,int capter);
Chainon* empiler(Chainon* pliste, Arbre* bebe);
AVL* rechercherAVL(AVL* a, char* id);
Arbre* insert(char* id, int nb);
AVL* insert_enfant(AVL* a, char* e, int* h, Arbre* enfant);
AVL* get_or_create(AVL* avl, char* id, int* h, Arbre** res);
Arbre* mega_arbre(FILE* US, FILE* SJ, FILE* JR, FILE* RU) ;

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
void afficherABR(Arbre* a, int niveau);
void afficherAVL(AVL* a);


//calculs
void calcul(Arbre* a, float* somme_fuites);

//fichiers
int recherche(AVL* a, char* e);
void ecrire(FILE* f, AVL* usine);

//main
int main(int argc, char* argv[]);

//memoire
void libererArbre(Arbre* a);
void libererAVL(AVL* a) ;



#endif // BIBLIO_H
