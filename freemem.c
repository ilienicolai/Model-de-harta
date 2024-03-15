/* NICOLAI Ilie - 313CB */
#include "structs.h"

// eliberare graf
void DistrG(TGL** ag)
{ 
    int i;
    AArc p, aux;
    for(i = 0; i <= (*ag)->n; i++){ 
        p = (*ag)->x[i];
        while(p)
        { 
          aux = p; p = p->urm;
          free(aux);
        }
  }
  free((*ag)->x);
  free(*ag);
  *ag = NULL;
}

// eliberare lista
void ElibLista(TLista *L) {
  TLista *p;
  while (L) {
    p = L;
    L= L->urm;
    free(p);
  }
}

// eliberare metrice
void elibmat(char **locuri, int N) {
  for (int i = 0; i <= N; i++) {
    free(locuri[i]);
  }
  free(locuri);
}