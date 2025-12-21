#include "biblio.h"

Chainon* creationChainon(Arbre* bebe) {
	Chainon* chainon=malloc(sizeof(Chainon));
	chainon->enfant=bebe;
	chainon->next=NULL;
	return chainon;
}



Chainon* empiler(Chainon* pliste, Arbre* bebe) {
	Chainon* chainon=creationChainon(bebe);
	chainon->next=pliste;
	return chainon;
}



void ecrire(FILE * f, AVL* usine ) {

    if(usine!=NULL){
        ecrire(f,usine->fg);
        fprintf(f, "%s;%d\n",usine->ID, usine->elmt);
        ecrire(f, usine->fd);
    }
}



AVL* rechercherAVL(AVL* a, char* id) {
	if (!a) return NULL;

	int c = strcmp(id, a->ID);
	if (c == 0) return a;
	if (c < 0) return rechercherAVL(a->fg, id);
	return rechercherAVL(a->fd, id);
}



Arbre* insert(char* id, int nb) {
	Arbre* new = malloc(sizeof(Arbre));
	if(!new) exit(66);

	new->ID = malloc(sizeof(char)*strlen(id)+1);
	strcpy (new->ID, id);
	

	if(!new->ID) exit(66);

	new->elmt = nb;
	new->enfants = NULL;
	new->nb_enfants=0;
	new->litre=-1;
	return new;
}



AVL* insert_enfant(AVL* a, char* e, int* h, Arbre* enfant) {

	if(a == NULL) {
		*h = 1;
		return creationStrAVL(enfant, e);
	}

	int z = strcmp(a->ID, e);

	if(z == 0) {
		printf("DC)jC  prC)sent\n");
		*h = 0;
		a->arbre->enfants=empiler(a->arbre->enfants,enfant);

		return a;
	}
	else if(z > 0) {
		a->fg = insert_enfant(a->fg, e, h, enfant);
		*h = -*h;
	}
	else {
		a->fd = insert_enfant(a->fd, e, h, enfant);
	}

	if(*h != 0) {
		a = equilibrage(a);

		if(a->equil == 0)
			*h = 0;
		else
			*h = 1;
	}

	return a;
}


AVL* get_or_create(AVL* avl, char* id, int* h, Arbre** res) {
	// Cherche d'abord le noeud dans l'AVL

	AVL* n = rechercherAVL(avl, id);
	
	if (n) {
		// L'ID existe dC)jC  : renvoie l'Arbre correspondant
		*res = n->arbre;
		*h = 0;  // pas de modification de hauteur

		return avl;
	}

	// L'ID n'exrbre

	Arbre* a = insert(id, 0);      // valeur initiale = 0
	// InsC(re le noiste pas : crC)er un nouvel Auvel Arbre dans l'AVL
	avl = insertStrAVL(avl, id, h, a);

	// Retourne le nouvel Arbre via res
	*res = a;


	return avl;
}



// Affiche un Arbre (ABR) avec indentation
void afficherABR(Arbre* a, int niveau) {
	if (!a) return;

	// Indentation selon le niveau
	for (int i = 0; i < niveau; i++) printf("  ");

	printf("%s (valeur = %.3f)\n", a->ID, a->elmt);

	// Affiche les enfants
	Chainon* c = a->enfants;
	while (c) {
		afficherABR(c->enfant, niveau + 1);
		c = c->next;
	}
}



// Affiche complet
void afficherAVL(AVL* a) {
	if (!a) return;

	// Sous-arbre gauche
	afficherAVL(a->fg);

	// Noeud courant
	printf("AVL: %s\n", a->ID);
	afficherABR(a->arbre, 1);  // enfants du noeud

	// Sous-arbre droit
	afficherAVL(a->fd);
}



void libererArbre(Arbre* a) {
    if (a==NULL){
        return;
    }
    
    // Libérer la liste des enfants
    Chainon* c=a->enfants;
    while (c!=NULL) {
        Chainon* temp=c;
        libererArbre(c->enfant);
        c=c->next;
        free(temp);
    }
    
    free(a->ID);
    free(a);
}



void libererAVL(AVL* a) {
    if (a==NULL) return;
    
    libererAVL(a->fg);
    libererAVL(a->fd);
    free(a->ID);
    free(a);
}



Arbre* mega_arbre(FILE* US, FILE* SJ, FILE* JR, FILE* RU) {
	char id[TAILLEID];
	char id2[TAILLEID];
	float fuite = 0;
	float max = 0;

	AVL* avl = NULL;
	int h = 0;
	Arbre* parent = NULL;
	Arbre* enfant = NULL;
	Arbre*usine=NULL;
	// --- Lecture du fichier US ---
	FILE* f = US;
	if (fscanf(f, "%21[^;];%f\n", id, &max) == 2) {
		avl = get_or_create(avl, id, &h, &parent);
		parent->elmt = max;
	}
	else {
            printf("ERREUR: Impossible de lire la première ligne du fichier US\n");
            return NULL;  // Retourner NULL explicitement
        }

    usine=parent;
	// --- Lecture des relations internes US ---
	while (fscanf(f, "%21[^;];%21[^;];%f\n", id, id2, &fuite) == 3) {
		parent = NULL;
		enfant = NULL;
	
		avl = get_or_create(avl, id, &h, &parent);

		avl = get_or_create(avl, id2, &h, &enfant);

		// mettre C  jour la valeur de l'enfant
		enfant->elmt = fuite;

		// ajouter enfant C  la liste chaC.nC)e du parent
		parent->enfants = empiler(parent->enfants, enfant);
		parent->nb_enfants+=1;
	
	
	}
	  
	
	// --- Lecture des autres fichiers SJ, JR, RU ---
	FILE* fichiers[3] = {SJ, JR, RU};

	for (int k = 0; k < 3; k++) {
	

		f = fichiers[k];
    
		while (fscanf(f, "%21[^;];%21[^;];%f\n", id, id2, &fuite) == 3) {
		   
    
			parent = NULL;
			enfant = NULL;

			avl = get_or_create(avl, id, &h, &parent);
			avl = get_or_create(avl, id2, &h, &enfant);

			enfant->elmt = fuite;
			parent->enfants = empiler(parent->enfants, enfant);
		    	parent->nb_enfants+=1;

	
		}


	
	}
    afficherAVL(avl);
    afficherABR(usine,0);

    return usine;

}



void calcul(Arbre* a,float* somme){
    if(a==NULL){
      *somme=-1;
      return;
    }
    if(a->enfants==NULL){
        *somme += a->litre;
        return;
    }
    
    if(a->litre==-1){
        a->litre=a->elmt;
    }
    printf("Noeud %s | litre = %.2f | nb_enfants = %d\n", a->ID, a->litre, a->nb_enfants);

    float vol=(a->litre)/a->nb_enfants;
    Chainon* temp=a->enfants;
    while(temp!=NULL){
        temp->enfant->litre=vol-(((temp->enfant->elmt)*vol)/100.0);
        calcul(temp->enfant,somme);
        temp=temp->next;
    }
    
    return;
}



int main(int argc, char* argv[]) {

    // passer US SJ JR RU
    FILE* f1 = fopen(argv[1], "r+");
    if(f1 == NULL){
        printf("Erreur ouverture fichier");
        exit(545);
    }
    FILE* f2 = fopen(argv[2], "r+");
    if(f2 == NULL){
        printf("Erreur ouverture fichier");
        exit(545);
    }
    FILE* f3 = fopen(argv[3], "r+");
    if(f3 == NULL){
        printf("Erreur ouverture fichier");
        exit(545);
    }
    FILE* f4 = fopen(argv[4], "r+");
    if(f4 == NULL){
        printf("Erreur ouverture fichier");
        exit(545);
    }
    Arbre* res = mega_arbre(f1,f2,f3,f4);

    if(res == NULL) {
        printf("ERREUR: Impossible de créer l'arbre (fichier US.csv vide ou mal formaté?)\n");
        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        return 1;
    }

    float max=res->elmt;
    float somme=NULL;
    somme=0;
    calcul(res, somme);
    printf("%s %f \n",res->ID,max-somme);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);


    /*
    int h=0;
    FILE* f=NULL;
    FILE* fichier=NULL;
    f=fopen(argv[1],"r+");
    if(f==NULL){
        exit(45);
    }
    fichier = fopen(argv[2], "w+");
    int a;
    char* ID = malloc(TAILLEID*sizeof(char));
    AVL* usine= NULL; 
    while (fscanf(f, "%21[^;];%d", ID, &a) == 2) {
        printf("LA %s ; %d\n", ID, a);
	    usine = insertAVL(usine, ID, &h, a);
    }   
    infixe(usine);
    ecrire(fichier, usine);
    if(fichier==NULL){
        exit(46);
    }
    fclose(fichier);
    fclose(f);
    */
    return 0;   
}
