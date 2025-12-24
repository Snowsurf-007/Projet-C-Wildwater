#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define TAILLEID 100



typedef struct AVL{
  int nom;
  double real;
  double max;
  double src;
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
int recherche(AVL* a, int b);
AVL* creationallAVL(int b, double max, double real, double src, char* c);
AVL* rotationGauche(AVL* a);
AVL* rotationDroite(AVL* a);
AVL* doubleRotationGauche(AVL* a);
AVL* doubleRotationDroite(AVL* a);
AVL* equilibrage(AVL* a);
AVL* insertalllAVL(AVL* a, char* e, int* h, int b, double max, double real, double src);
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



int recherche(AVL* a, int b){
    if(a == NULL)
        return 1;

    //int z = strcmp(a->ID, e);

    if(a->nom == b)
        return 0;
    else if(a->nom > b)
        return recherche(a->fg, b);
    else
        return recherche(a->fd, b);
}



AVL* creationRealAVL(int b, double max, double real, double src, char* c){
    AVL* newNode = malloc(sizeof(AVL));
    if(!newNode){
        printf("Erreur : malloc\n");
        exit(1);
    }
    
    newNode->nom = b;
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

void traiter(AVL* a){
    if(a != NULL)
        printf("b= %d;max=%f real=%f src=%f (%s)  eq=%d\n", a->nom, a->max, a->real, a->src, a->ID, a->equil);
}

/* =====================
   INSERTION AVL
   ===================== */
AVL* insertRealAVL(AVL* a, char* e,int* h, int b, double max, double real, double src) {
    if (a == NULL) {
    	*h=1;
        return creationRealAVL(b, max, real, src, e);
    }
    //int z = strcmp(a->ID, e);

    if (a->nom == b) {

        if(a->max==0){
        a->max = a->max+ max;
        }
        if(a->real==0){
        a->real = a->real+ real;
        }
        if(a->src==0){
        a->src = a->src+ src;
        }
        traiter(a);
        return a;
       
    }
    else if (a->nom > b) {
        a->fg = insertRealAVL(a->fg, e, h, b, max, real, src);
        *h=-*h;
    }
    else if(a->nom < b){
        a->fd = insertRealAVL(a->fd, e, h, b, max, real, src);
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

void infixe(AVL* a){
    if(a == NULL) return;
    infixe(a->fg);
    traiter(a);
    infixe(a->fd);
}


int main(int argc, char* argv[]){
	printf(" lancer\n");
    argc+=1; //pour eviter le warning
    int h=0;
    FILE* fnom=NULL;
    FILE* fmax=NULL;
    FILE* freal=NULL;
    FILE* fsrc=NULL;
    FILE* fichier=NULL;
    fnom=fopen(argv[1],"r+");
    fmax=fopen(argv[2],"r+");
    freal=fopen(argv[3],"r+");
    fsrc=fopen(argv[4],"r+");
    if(fnom==NULL){
        exit(5);
    }
    if(fmax==NULL){
        exit(45);
    }
    if(freal==NULL){
        exit(55);
    }
    if(fsrc==NULL){
        exit(35);
    }
    fichier = fopen(argv[5], "w+");
    if(fichier==NULL){
        exit(0);
    }
    int b=0;
    double c;
    char* ID =malloc(TAILLEID*sizeof(char));
    AVL* usine= NULL;
    //printf("passer\n");
    while (fscanf(fnom, "%s", ID) == 1) {
	//printf("%s\n",ID);
	b=b+1;
	usine = insertRealAVL(usine, ID, &h, b, c, 0, 0);
    }
    //infixe(usine);
    printf(" sortie 1\n");
     printf("la c'est valpour 1 b=%d", b);    
    char ligne[b];
    double d;
b=0;
while (fgets(ligne, sizeof ligne, fmax)) {
    char *end;
    c= strtof(ligne, &end);
    if (end == ligne) continue; // ignore lignes invalides
    b++;
    usine = insertRealAVL(usine, ID, &h, b, c, 0, 0);
}
    printf("la c'est val b=%d", b); 
 b=0;
    while (fgets(ligne, sizeof ligne, freal)) {
    char *end;
    c= strtof(ligne, &end);
    if (end == ligne) continue; // ignore lignes invalides
    b++;
    usine = insertRealAVL(usine, ID, &h, b, 0, c, 0);
}
b=0;
while (fgets(ligne, sizeof ligne, fsrc)) {
    char *end;
    c= strtof(ligne, &end);
    if (end == ligne) continue; // ignore lignes invalides
    b++;
    usine = insertRealAVL(usine, ID, &h, b, 0, 0, c);
}
/*infixe(usine);
printf("la c'est val b=%d", b); 
    //printf("\n 1ER\n");
    //infixe(usine);
     //printf(" entrer 2\n");
    b=0;
    while (fscanf(fmax, "%f", &c) == 1) {
	//printf("%f\n",c);
	b=b+1;
	usine = insertRealAVL(usine, ID, &h, b, c, 0, 0);
    }
    /*printf("\n 2EME\n");
    infixe(usine);
    b=0;
    while (fscanf(fmax, "%f", &c) == 1) {
	//printf("%f\n",c);
	b=b+1;
	usine = insertRealAVL(usine, ID, &h, b, c, 0, 0);
    } */
    //printf("\n 3EME\n");
    //infixe(usine);
    ecrire(fichier, usine);
    fclose(fichier);
    fclose(fmax);
    fclose(freal);
    fclose(fsrc);
    free(ID);
    return 0;
}
