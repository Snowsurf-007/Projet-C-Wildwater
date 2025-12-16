#ifndef BIBLIO_H
#define BIBLIO_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define TAILLEID 20

typedef struct AVL{
  int elmt;
  int equil;
  Char* ID
  struct AVL* fg;
  struct AVL* fd;
}AVL;



typedef struct Chainon{
  AVL elmt;
  struct Chainon* next;
}Chainon;



typedef struct File{
  struct Chainon* head;
  struct Chainon* tail;
}File;



int main(int argc, char* argv[]);
int max(int a, int b);
int min(int a, int b);
int hauteur(AVL* a);
int equilibre(AVL* a);
int recherche(AVL* a, char* e);
AVL* creationAVL(int e, char* c);
AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);
AVL* equilibrage(AVL* a);
AVL* insertStrAVL(AVL* a, char* e, int* h, int nb);
void traiter(AVL* a);
void infixe(AVL* a);
void prefixe(AVL* a);
void suffixe(AVL* a);
void recupAVL(FILE* f);



#endif // BIBLIO_H
