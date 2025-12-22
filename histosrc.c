#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define TAILLEID 100



typedef struct AVL{
  int elmt;
  int equil;
  char* ID;
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



//#endif // BIBLIO_H
int max(int a, int b){
    return (a > b) ? a : b;
}



int min(int a, int b){
    return (a < b) ? a : b;
}



int hauteur(AVL* a){
    if(a == NULL) return -1;
    return 1 + max(hauteur(a->fg), hauteur(a->fd));
}



int equilibre(AVL* a){
    if(a == NULL) return 0;
    return hauteur(a->fd) - hauteur(a->fg);
}



int recherche(AVL* a, char* e){
    if(a == NULL)
        return 1;

    int z = strcmp(a->ID, e);

    if(z == 0)
        return 0;
    else if(z > 0)
        return recherche(a->fg, e);
    else
        return recherche(a->fd, e);
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
   ROTATION GAUCHE
   ===================== */
AVL* rotationGauche(AVL* a){
    AVL* p = a->fd;

    a->fd = p->fg;
    p->fg = a;

    a->equil = equilibre(a);
    p->equil = equilibre(p);

    return p;
}



/* =====================
   ROTATION DROITE
   ===================== */
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

    if(a->equil == 2){ // trop à droite
        if(a->fd->equil < 0)
            return doubleRotationGauche(a);
        else
            return rotationGauche(a);
    }
    else if(a->equil == -2){ // trop à gauche
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
AVL* insertStrAVL(AVL* a, char* e,int* h,int capter) {
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
        a->fg = insertStrAVL(a->fg, e, h, capter);
        *h=-*h;
    }
    else if(z < 0){
        a->fd = insertStrAVL(a->fd, e, h, capter);
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



void ecrire(FILE * f, AVL* usine) {

    if(usine!=NULL){
        ecrire(f,usine->fg);
        fprintf(f, "%s;%d\n",usine->ID, usine->elmt);
        ecrire(f, usine->fd);
    }
}



int main(int argc, char* argv[]){
    argc+=1; //pour eviter le warning
    int h=0;
    FILE* f=NULL;
    FILE* fichier=NULL;
    f=fopen(argv[1],"r+");
    if(f==NULL){
        exit(45);
    }
    fichier = fopen(argv[2], "w+");
    if(fichier==NULL){
        exit(0);
    }
    int a;
    char* ID =malloc(TAILLEID*sizeof(char));
    AVL* usine= NULL; 
    while (fscanf(f, "%100[^;];%d", ID, &a) == 2) {
    	usine = insertStrAVL(usine, ID, &h, a);
    }
    ecrire(fichier, usine);
    fclose(fichier);
    fclose(f);
    free(ID);
    return 0;
}
