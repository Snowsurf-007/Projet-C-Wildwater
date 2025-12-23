#include "biblio.h"



typedef struct AVL{
  float real;
  float max;
  float src;
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
AVL* creationallAVL(float max, float real, float src, char* c);
AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);
AVL* equilibrage(AVL* a);
AVL* insertalllAVL(AVL* a, char* e, int* h, float max, float real, float src);
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



AVL* creationRealAVL(float max, float real, float src, char* c){
    AVL* newNode = malloc(sizeof(AVL));
    if(!newNode){
        printf("Erreur : malloc\n");
        exit(1);
    }

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
AVL* insertRealAVL(AVL* a, char* e,int* h,float max, float real, float src) {
    if (a == NULL) {
    	*h=1;
        return creationRealAVL(max, real, src, e);
    }
    int z = strcmp(a->ID, e);

    if (z == 0) {
        //printf("Cet élément est déjà présent dans l'AVL\n");
        if(max!=0){
        a->max = a->max+ max;
        return a;
        }
        else if(real!=0){
        a->real = a->real+ real;
        return a;
        }
        else if(src!=0){
        a->src = a->src+ src;
        return a;
        }
       
    }
    else if (z > 0) {
        a->fg = insertRealAVL(a->fg, e, h, max, real, src);
        *h=-*h;
    }
    else if(z < 0){
        a->fd = insertRealAVL(a->fd, e, h, max, real, src);
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
        fprintf(f, "%s;%f;%f;%f\n",usine->ID, usine->max, usine->real, usine->src);
        ecrire(f, usine->fd);
    }
}
void traiter(AVL* a){
    if(a != NULL)
        printf("max=%f real=%f src=%f (%s)  eq=%d\n", a->max, a->real, a->src, a->ID, a->equil);
}

void infixe(AVL* a){
    if(a == NULL) return;
    infixe(a->fg);
    traiter(a);
    infixe(a->fd);
}


int main(int argc, char* argv[]){
	printf(" lancer");
    argc+=1; //pour eviter le warning
    int h=0;
    FILE* fmax=NULL;
    FILE* freal=NULL;
    FILE* fsrc=NULL;
    FILE* fichier=NULL;
    fmax=fopen(argv[1],"r+");
    freal=fopen(argv[2],"r+");
    fsrc=fopen(argv[3],"r+");
    if(fmax==NULL){
        exit(45);
    }
    if(freal==NULL){
        exit(55);
    }
    if(fsrc==NULL){
        exit(35);
    }
    fichier = fopen(argv[4], "w+");
    if(fichier==NULL){
        exit(0);
    }
    float a;
    float b;
    float c;
    char* ID =malloc(TAILLEID*sizeof(char));
    AVL* usine= NULL; 
    while (fscanf(fmax, "%100[^;];%f", ID, &a) == 2) {
	c=a/1.0;
	printf("%f",c);
	usine = insertRealAVL(usine, ID, &h, a, 0, 0);
    	c=0;
    }  
    printf("\n 1ER\n");
    infixe(usine);
   
    while (fscanf(freal, "%100[^;];%f", ID, &a) == 2) {
	c=a/1.0;
	printf("%f",c);
	usine = insertRealAVL(usine, ID, &h, 0, a, 0);
    	c=0;
    }
    printf("\n 2EME\n");
     infixe(usine);
    while (fscanf(freal, "%100[^;];%f", ID, &a) == 2) {
	c=a/1.0;
	printf("%f",c);
	usine = insertRealAVL(usine, ID, &h, 0, 0, a);
    	c=0;
    }
    printf("\n 3EME\n");
    infixe(usine);
    ecrire(fichier, usine);
    fclose(fichier);
    fclose(fmax);
    fclose(freal);
    fclose(fsrc);
    free(ID);
    return 0;
}
