/* NICOLAI Ilie - 313CB */
#include "structs.h"

// cautare locuri
// indexate de la 1
int cauta_locuri(char *n_nod, char **locuri, int n) {
    int i = 0;
    for (i = 1; i <= n; i++) {
        // daca nodul exista, se returneaza indicele
        if (!strcmp(locuri[i], n_nod)) {
            return i;
        } else {
            // daca nu exista se adauga si se returneaza indicele
            if (locuri[i][0]=='\0') {
                strcpy(locuri[i], n_nod);
                return i;
            }
        }
    }
}

// citire harta
void Citire_Harta_Task_1(TGL *G, char **locuri, FILE *fin, int M) {
    // nod destinatie
    char n_dest[15];
    // nod sursa
    char n_src[15];
    int i = 0;
    int dest = 0, src = 0; // indicii destinatiei si sursei
    int cost = 0; // costul
    AArc *p, aux;
    for (i = 1; i <= M; i++) {
        // citire sursa
        fscanf(fin, "%s ", n_src);
        // determinare indice sursa
        src = cauta_locuri(n_src, locuri, G->n);
        // citire destinatie
        fscanf(fin, "%s ", n_dest);
        // determinarer indice sursa
        dest = cauta_locuri(n_dest, locuri, G->n);
        // citire cost
        fscanf(fin, "%d", &cost);
        // adaugare muchii
        // inserare ordonata in lista de adiacenta
        // adaugare muchie directa src - dest
        p = G->x + src;
        while (*p && (*p)->d < dest) { // determinare loc inserare
            p = &(*p)->urm;
        }
        // alocare arc
        aux = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux) {
            DistrG(&G);
            printf("error3\n");
            return;
        }
        // actualizare legaturi     
        aux->urm = *p; *p = aux;
        aux->d = dest; aux->c = cost;
        // adaugare muchie inversa dest - src
        p = G->x + dest;
        while (*p && (*p)->d < src) { // determinare loc inserare
            p = &(*p)->urm;
        }
        // alocare arc
        aux = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux) {
            DistrG(&G);
            printf("error4\n");
            return ;
        }
        // actualizare legaturi
        aux->urm = *p; *p = aux;
        aux->d = src; aux->c = cost;
    }
}

// determinare distanta minima
int mindist(int *dist, int *vis, int n) {
  int min=__INT_MAX__;
  int node = 0;
  for (int i = 1; i <= n; i++) {
    if(vis[i] == 0 && dist[i] < min) {
      min = dist[i];
      node = i;
    }
  }
  return node;
}

// determinare drum minim
void arbprim(TGL *g, int *dist, int *vis) {
  int node;
  for (int i=1; i<=g->n; i++) {
    // determinare nod cu distanta cea mai mica
    node=mindist(dist, vis, g->n);
    // marcarre nod ca vizitat
    vis[node]=1;
    AArc L = g->x[node];
    // parcurgere lista de adiacenta
    while((L)) {
      // actualizare distante
      if(vis[(L)->d]==0 && L->c < dist[L->d]) {
        dist[L->d]=L->c;
      }
      L=L->urm;
    }
  }
}
