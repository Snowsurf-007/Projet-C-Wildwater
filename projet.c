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



void ecrire(FILE* f, AVL* usine) {
    if(usine != NULL) {
        ecrire(f, usine->fg);
        fprintf(f, "%s;%f\n", usine->ID, usine->elmt);
        ecrire(f, usine->fd);
    }
}



void ecrireReal(FILE* f, AVL* usine) {
    if(usine != NULL) {
        ecrireReal(f, usine->fg);
        fprintf(f, "%s;%f;%f;%f\n", usine->ID, usine->max, usine->real, usine->src);
        ecrireReal(f, usine->fd);
    }
}



void mode1(char* inputFile, char* outputFile) {

        int h = 0;
        FILE* f = fopen(inputFile, "r");
        
        if(f == NULL) {
            printf("Erreur: impossible d'ouvrir %s\n", inputFile);
            exit(45);
        }
        
        FILE* fichier = fopen(outputFile, "w");
        
        if(fichier == NULL) {
            printf("Erreur: impossible de créer %s\n", outputFile);
            fclose(f);
            exit(46);
        }
        
        int a;
        char* ID = malloc(TAILLEID * sizeof(char));
        AVL* usine = NULL;
        
        while (fscanf(f, "%99[^;];%d", ID, &a) == 2) {
            usine = insertAVL(usine, ID, &h, a);
        }
        
        ecrire(fichier, usine);
        
        fclose(fichier);
        fclose(f);
        free(ID);
        libererAVL(usine);
}



void mode2(char* inputFile, char* outputFile) {

        int h = 0;
        FILE* f = fopen(inputFile, "r");
        
        if(f == NULL) {
            printf("Erreur: impossible d'ouvrir %s\n", inputFile);
            exit(47);
        }
        
        FILE* fichier = fopen(outputFile, "w");
        
        if(fichier == NULL) {
            printf("Erreur: impossible de créer %s\n", outputFile);
            fclose(f);
            exit(48);
        }
        
        int a;
        float b, c;
        char* ID = malloc(TAILLEID * sizeof(char));
        AVL* usine = NULL;
        
        while (fscanf(f, "%100[^;];%d;%f", ID, &a, &b) == 3) {
            c = a / 1.0 - (a * (b / 100));
            usine = insertAVL(usine, ID, &h, c);
            c = 0;
        }
        
        ecrire(fichier, usine);
        
        fclose(fichier);
        fclose(f);
        free(ID);
        libererAVL(usine);
}



void mode3(char* maxFile, char* realFile, char* srcFile, char* outputFile) {

        int h = 0;
        
        FILE* fmax = fopen(maxFile, "r");
        FILE* freal = fopen(realFile, "r");
        FILE* fsrc = fopen(srcFile, "r");
        
        if(fmax == NULL || freal == NULL || fsrc == NULL) {
            printf("Erreur: impossible d'ouvrir les fichiers d'entrée\n");
            if(fmax) fclose(fmax);
            if(freal) fclose(freal);
            if(fsrc) fclose(fsrc);
            exit(45);
        }
        
        FILE* fichier = fopen(outputFile, "w");
        
        if(fichier == NULL) {
            printf("Erreur: impossible de créer %s\n", outputFile);
            fclose(fmax);
            fclose(freal);
            fclose(fsrc);
            exit(0);
        }
        
        float a;
        char* ID = malloc(TAILLEID * sizeof(char));
        AVL* usine = NULL;
        
        // Lecture du fichier max
        while (fscanf(fmax, "%99[^;];%f", ID, &a) == 2) {
            usine = insertRealAVL(usine, ID, &h, a, 0, 0);
        }
        
        // Lecture du fichier real
        rewind(freal);
        while (fscanf(freal, "%99[^;];%f", ID, &a) == 2) {
            usine = insertRealAVL(usine, ID, &h, 0, a, 0);
        }
        
        // Lecture du fichier src
        while (fscanf(fsrc, "%99[^;];%f", ID, &a) == 2) {
            usine = insertRealAVL(usine, ID, &h, 0, 0, a);
        }
        
        ecrireReal(fichier, usine);
        
        fclose(fichier);
        fclose(fmax);
        fclose(freal);
        fclose(fsrc);
        free(ID);
        libererAVL(usine);
}



void mode4(char* suFile, char* usFile, char* sjFile, char* jrFile, char* ruFile) {
        // passer SU US SJ JR RU et les verifier
        FILE* f1 = fopen(suFile, "r+");
        if(f1 == NULL){
            printf("Erreur ouverture fichier SU\n");
            exit(55);
        }
        FILE* f2 = fopen(usFile, "r+");
        if(f2 == NULL){
            printf("Erreur ouverture fichier US\n");
            exit(55);
        }
        FILE* f3 = fopen(sjFile, "r+");
        if(f3 == NULL){
            printf("Erreur ouverture fichier SJ\n");
            exit(45);
        }
        FILE* f4 = fopen(jrFile, "r+");
        if(f4 == NULL){
            printf("Erreur ouverture fichier JR\n");
            exit(45);
        }
        FILE* f5 = fopen(ruFile, "r+");
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
            return;
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


int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("Usage:\n");
        printf("  Mode 1: %s 1 input.csv output.csv\n", argv[0]);
        printf("  Mode 2: %s 2 input.csv output.csv\n", argv[0]);
        printf("  Mode 3: %s 3 max.csv real.csv src.csv output.csv\n", argv[0]);
        return 1;
    }
    
    int mode = atoi(argv[1]);
    
    switch(mode) {
        case 1:
            if(argc != 4) {
                printf("Mode 1 nécessite: %s 1 input.csv output.csv\n", argv[0]);
                return 1;
            }
            mode1(argv[2], argv[3]);
            break;
            
        case 2:
            if(argc != 4) {
                printf("Mode 2 nécessite: %s 2 input.csv output.csv\n", argv[0]);
                return 1;
            }
            mode2(argv[2], argv[3]);
            break;
            
        case 3:
            if(argc != 6) {
                printf("Mode 3 nécessite: %s 3 max.csv real.csv src.csv output.csv\n", argv[0]);
                return 1;
            }
            mode3(argv[2], argv[3], argv[4], argv[5]);
            break;
        
        case 4:
            if(argc != 7) {
                printf("Mode 4 nécessite: %s 4 SU.csv US.csv SJ.csv JR.csv RU.csv \n", argv[0]);
                return 1;
            }
            mode4(argv[2], argv[3], argv[4], argv[5], argv[6]);
            break;
                                
        default:
            printf("Mode invalide. Utilisez 1, 2, 3 ou 4.\n");
            return 1;
    }
    
    return 0;
}
