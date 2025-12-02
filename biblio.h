#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>



typedef struct Chainon{
  AVL elmt;
  struct Chainon* next;
}Chainon;



typedef struct File{
  struct Chainon* head;
  struct Chainon* tail;
}File;



typedef struct AVL{
  int elmt;
  int equil;
  struct AVL* fg;
  struct AVL* fd;
}AVL;



typedef AVL* pArbre;



typedef File* pFile;
