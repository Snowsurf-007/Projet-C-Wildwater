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





#endif // BIBLIO_H
