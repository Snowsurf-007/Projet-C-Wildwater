#include "biblio.h"


//fonction chainon
Chainon* creationChainon(Arbre* bebe) {
	Chainon* chainon=malloc(sizeof(Chainon));
	//verification malloc
	if(chainon==NULL){
	  exit(87);
	}
	chainon->enfant=bebe;
	chainon->next=NULL;
	return chainon;
}


//creation d'une pile
Chainon* empiler(Chainon* pliste, Arbre* bebe) {
	Chainon* chainon=creationChainon(bebe);
	chainon->next=pliste;
	return chainon;
}


//recherche un ID dans l'AVL
AVL* rechercherAVL(AVL* a, char* id) {
	if (!a){
	    return NULL;
	}

	int c = strcmp(id, a->ID);
	
	//si trouvé
	if (c == 0){
	    return a;
	}
	//si plus petit
	if (c < 0){
	    return rechercherAVL(a->fg, id);
	}
	//si plus grand
	else{
	    return rechercherAVL(a->fd, id);
	}
}


//inserer une feuille/un noeud dans l'arbre
Arbre* insert(char* id, int nb) {
	Arbre* new = malloc(sizeof(Arbre));
	//verification du malloc
	if (new==NULL){
	  exit(54);
	}
	new->ID = malloc(sizeof(char)*strlen(id)+1);
	//verification du malloc
	if (new->ID==NULL){
	  exit(57);
	}
	strcpy (new->ID, id);
	
	//initialisation des donnees
	new->elmt = nb;
	new->enfants = NULL;
	new->nb_enfants=0;
	new->litre=-1;
	return new;
}



//recupere ou cree un noeud
AVL* get_or_create(AVL* avl, char* id, int* h, Arbre** res) {
	
	// Cherche d'abord le noeud dans l'AVL
	AVL* n = rechercherAVL(avl, id);
	
	if (n) {
		// L'ID existe : renvoie l'Arbre correspondant
		*res = n->arbre;
		*h = 0;  // pas de modification de hauteur

		return avl;
	}

	Arbre* a = insert(id, 0);      // valeur initiale = 0
	// Si il n'existe pas : creer un nouvel Arbre dans l'AVL
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



//fonction liberation memoire d'arbre
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



//fonction liberation memoire d'AVL
void libererAVL(AVL* a) {
    if (a==NULL){
        return;
    }
    
    libererAVL(a->fg);
    libererAVL(a->fd);
    free(a->ID);
    free(a);
}



//rempli un l'abr simulant le reseau
Arbre* mega_arbre(FILE* US, FILE* SJ, FILE* JR, FILE* RU) {
	char id[TAILLEID];
	char id2[TAILLEID];
	double fuite = 0;
	double max = 0;

	AVL* avl = NULL;
	int h = 0;
	Arbre* parent = NULL;
	Arbre* enfant = NULL;
	Arbre* usine = NULL;
	// --- Lecture du fichier US ---
	FILE* f = US;
	if (fscanf(f, "%99[^;];%lf\n", id, &max) == 2) {
		avl = get_or_create(avl, id, &h, &parent);
		parent->elmt = max;
	}
	else {
            printf("ERREUR: Impossible de lire la première ligne du fichier US\n");
            return NULL;  // Retourner NULL explicitement
        }

        usine=parent;
	// --- Lecture des relations internes US ---
	while (fscanf(f, "%99[^;];%99[^;];%lf\n", id, id2, &fuite) == 3) {
		parent = NULL;
		enfant = NULL;
	
		avl = get_or_create(avl, id, &h, &parent);
		avl = get_or_create(avl, id2, &h, &enfant);

		// mettre a jour la valeur de l'enfant
		enfant->elmt = fuite;

		// ajouter enfant a la liste chainee du parent
		parent->enfants = empiler(parent->enfants, enfant);
		parent->nb_enfants+=1;
	}
	  
	// --- Lecture des autres fichiers SJ, JR, RU ---
	FILE* fichiers[3] = {SJ, JR, RU};

	for (int k = 0; k < 3; k++) {
	
		f = fichiers[k];
    
		while (fscanf(f, "%99[^;];%99[^;];%lf\n", id, id2, &fuite) == 3) {
			parent = NULL;
			enfant = NULL;

			avl = get_or_create(avl, id, &h, &parent);
			avl = get_or_create(avl, id2, &h, &enfant);
                        
                        // mettre a jour la valeur de l'enfant
			enfant->elmt = fuite;
			
			// ajouter enfant a la liste chainee du parent
			parent->enfants = empiler(parent->enfants, enfant);
		    	parent->nb_enfants+=1;
		}
	}
	libererAVL(avl);
        return usine;
}


//somme des trajets sources usines
float source(FILE* f){
    char source[99];
    char unit[99];
    float volume;
    float pourcentage;
    float res=0;
    
    //verifie qu'il y a bien 4 données dans SU
    while (fscanf(f,"%99[^;];%99[^;];%f;%f",source, unit, &volume, &pourcentage) == 4){
        res+=volume*(1-(pourcentage/100));
    }
    return res;
}



//calcul l'eau restante aprés toutes les fuites
void calcul(Arbre* a, double* somme) {
    if(a == NULL) {
        return;
    }
    
    // Initialiser le volume à ce nœud si c'est la racine
    if(a->litre == -1) {
        a->litre = a->elmt;  // Volume initial à la racine
    }
    
    // Si c'est une feuille, pas de distribution
    if(a->enfants == NULL) {
        return;
    }
    
    // Calculer le volume à distribuer à chaque enfant
    double vol_par_enfant = a->litre / a->nb_enfants;
    
    // Parcourir tous les enfants
    Chainon* temp = a->enfants;
    while(temp != NULL) {
        // Calculer la fuite pour cet enfant
        double volume = (temp->enfant->elmt * vol_par_enfant) / 100.0;
        
        // additionner la fuite au total
        *somme += volume;
        
        // Le volume qui arrive à l'enfant (après la fuite)
        temp->enfant->litre = vol_par_enfant - volume;
        
        // Récursion sur l'enfant
        calcul(temp->enfant, somme);
        
        temp = temp->next;
    }
}



int main(int argc, char* argv[]) {

    //verifie que le nombre d'arguments passées et le bon
    if (argc==6){
        // passer SU US SJ JR RU et les verifier
        FILE* f1 = fopen(argv[1], "r+");
        if(f1 == NULL){
            printf("Erreur ouverture fichier SU\n");
            exit(55);
        }
        FILE* f2 = fopen(argv[2], "r+");
        if(f2 == NULL){
            printf("Erreur ouverture fichier US\n");
            exit(55);
        }
        FILE* f3 = fopen(argv[3], "r+");
        if(f3 == NULL){
            printf("Erreur ouverture fichier SJ\n");
            exit(45);
        }
        FILE* f4 = fopen(argv[4], "r+");
        if(f4 == NULL){
            printf("Erreur ouverture fichier JR\n");
            exit(45);
        }
        FILE* f5 = fopen(argv[5], "r+");
        if(f5 == NULL){
            printf("Erreur ouverture fichier RU\n");
            exit(65);
        }
		
        Arbre* res = mega_arbre(f2,f3,f4,f5);

	//probleme dans la création de méga arbre
        if(res == NULL) {
            printf("ERREUR: Impossible de créer l'arbre\n");
            fclose(f1);
            fclose(f2);
            fclose(f3);
            fclose(f4);
            fclose(f5);
            return 1;
        }
        double max=res->elmt;
	res->elmt=source(f1);
	double src=res->elmt;
        double somme=0.0;
        calcul(res, &somme);
        float pourcentage = (somme / src) * 100;
        
        // Afficher le résultat
        printf("=== RÉSULTAT ===\n");
        printf("Usine: %s\n", res->ID);
        
        //A FAIRE IMPERATIVEMENT
        

        printf("Quantité captée: %.2lf k.m^3\n", src);

        
        //A FAIRE IMPERATIVEMENT
        
        printf("Capacité maximale: %.2lf k.m^3\n", max);
        printf("Total des fuites: %.2lf k.m^3\n", somme);
        printf("Volume restant: %.2lf k.m^3\n", (src - somme));
        printf("Pourcentage de fuite: %.3f %% \n\n", pourcentage);

	// Libération mémoire
	libererArbre(res);

	//fermeture des fichiers
        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        fclose(f5);
    }

	//si mauvais nombre d'arguments
    else{
	printf("ERREUR: Nombre d'arguments mauvais\n");
        return 2;
    }
    
    return 0;   
}
