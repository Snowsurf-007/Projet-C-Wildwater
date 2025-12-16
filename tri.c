#include "biblio.h"

Chainon* creationChainon(Arbre* bebe) {
	Chainon* chainon=malloc(sizeof(chainon));
	chainon->enfant=bebe;
	chainon->next=NULL;
	return chainon;
}
Chainon * empiler(Chainon* pliste, Arbre* bebe) {
	Chainon* chainon=creationChainon(bebe);
	chainon->next=pliste;
	return chainon;
}

void affichage(Arbre* a,int niveau) {
     if (a == NULL) return;

    // Affiche le nœud courant avec indentation
    for (int i = 0; i < niveau; i++) printf("  "); // 2 espaces par niveau
    printf("ID: %s, elmt: %d\n", a->ID, a->elmt);

    // Parcours de la liste chaînée des enfants
    Chainon* c = a->enfants;
    while (c != NULL) {
        affichage(c->enfant, niveau + 1);
        c = c->next;
    }

}


void mega_arbre(FILE* US,FILE* SJ,FILE* JR,FILE* RU) {
	char* id=malloc(TAILLEID*sizeof(char));
	if(id==NULL) {
		exit(545);
	}
	char* id2=malloc(TAILLEID*sizeof(char));
	if(id2==NULL) {
		exit(545);
	}
	float fuite=-1;
	AVL*avl=NULL;
	int h=0;
	Arbre* a = NULL;
	FILE* f=US;
	while (fscanf(f, "%21[^;]", id) == 1) {   // lit jusqu'C  ';'
		fgetc(f);    // consomme le ';'
		fscanf(f, "%21[^;]", id2);
		fgetc(f);    // consomme le ';'
		fscanf(f, "%f", &fuite);      // lit le nombre
		fgetc(f);                             // consomme le '\n'
		//printf("ID AMONT: %s  ID AVAL %s  fuites %f \n",id,id2,fuite);
		avl=insertStrAVL(avl, id, &h,fuite);
		avl=insertStrAVL(avl, id2,&h,0);
		//creation2(id,id2,fuite);
	}
	 f=SJ;
	while (fscanf(f, "%21[^;]", id) == 1) {   // lit jusqu'C  ';'
		fgetc(f);    // consomme le ';'
		fscanf(f, "%21[^;]", id2);
		fgetc(f);    // consomme le ';'
		fscanf(f, "%f", &fuite);      // lit le nombre
		fgetc(f);                             // consomme le '\n'
		//printf("ID AMONT: %s  ID AVAL %s  fuites %f \n",id,id2,fuite);
		//creation2(id,id2,fuite);
		avl=insertStrAVL(avl, id, &h,fuite);
		avl=insertStrAVL(avl, id2,&h,0);
	}
	 f=JR;
	while (fscanf(f, "%21[^;]", id) == 1) {   // lit jusqu'C  ';'
		fgetc(f);    // consomme le ';'
		fscanf(f, "%21[^;]", id2);
		fgetc(f);    // consomme le ';'
		fscanf(f, "%f", &fuite);      // lit le nombre
		fgetc(f);                             // consomme le '\n'
		//printf("ID AMONT: %s  ID AVAL %s  fuites %f \n",id,id2,fuite);
		//creation2(id,id2,fuite);
		avl=insertStrAVL(avl, id, &h,fuite);
		avl=insertStrAVL(avl, id2,&h,0);
	}
	 f=RU;
	while (fscanf(f, "%21[^;]", id) == 1) {   // lit jusqu'C  ';'
		fgetc(f);    // consomme le ';'
		fscanf(f, "%21[^;]", id2);
		fgetc(f);    // consomme le ';'
		fscanf(f, "%f", &fuite);      // lit le nombre
		fgetc(f);                             // consomme le '\n'
		//printf("ID AMONT: %s  ID AVAL %s  fuites %f \n",id,id2,fuite);
		//creation2(id,id2,fuite);
		avl=insertStrAVL(avl, id, &h,fuite);
		avl=insertStrAVL(avl, id2,&h,0);
	}
	infixe(avl);
	//printf("%s  %f",a->ID,a->elmt);
}