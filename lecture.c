#include "biblio.h"
int main(int argc, char* argv[]){
   // printf("rentre");
    FILE* f=NULL;
    f=fopen(argv[1],"r+");
    if(f==NULL){
        exit(545);
    }
    char* c=malloc(TAILLEID*sizeof(char));
    if(c==NULL){
        exit(545);
    }
    int a;
   while (fscanf(f, "%99[^;]", c) == 1) {   // lit jusqu'à ';'
    fgetc(f);                             // consomme le ';'
    fscanf(f, "%d", &a);      // lit le nombre
    fgetc(f);                             // consomme le '\n'
        

        printf("Chaine : %s\n",c);
        printf("Nombre : %d\n" ,a);
    }
  // il faut mettre dans l histogramme
    return 0;
}
