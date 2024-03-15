/* NICOLAI Ilie - 313CB */
#include "structs.h"

// determina indicele nodului
int determina_indice(char *nod) {
    // Insula are indice 0
    if (!strcmp(nod, "Insula")) {
        return 0;
    }
    // Corabia are indice 1
    if (!strcmp(nod, "Corabie")) {
        return 1;
    }
    // restul de noduri au indice egal cu numarul
    int i = 4;
    int num = 0;
    while (nod[i]) {
        num = num * 10 + (nod[i]-'0');
        i++;
    }
    return num;
}

// citire harta
void Citire_Harta_Task_2(TGL *G, int M, FILE *fin) {
    // nod destinatie
    char n_dest[15];
    // nod sursa
    char n_src[15];
    int i = 0;
    int dest = 0, src = 0; // indicii destinatiei si sursei
    int cost = 0;   // costul
    AArc *p, aux;   // listele de arce
    for (i = 0; i < M; i++) {
        // citire nod sursa
        fscanf(fin, "%s", n_src);
        // determinare indice
        src = determina_indice(n_src);
        // citire nod destinatie
        fscanf(fin, "%s", n_dest);
        // determinare indice
        dest = determina_indice(n_dest);
        // citire cost
        fscanf(fin, "%d", &cost);
        // inserare muchie
        p = G->x + src;
        // inserare ordonata
        while (*p && (*p)->d < dest) {  // determinare loc de inserare
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
    }
}

// citire adancimi
void citire_adancimi(int *dep, int N, FILE *fin) {
    char nod[15];
    int a = 0;
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%s", nod);
        fscanf(fin, "%d", &a);
        dep[i] = a;
    }
}

// determinare distanta minima din vector
int det_min_dist(float *dist, int *vis, int n) {
  float min=__INT_MAX__;
  int node = 0;
  for (int i = 0; i < n; i++) {
    if(vis[i] == 0 && dist[i] < min) {
      min = dist[i];
      node = i;

    }
  }
  
  return node;
}

// determinare drumuri - algoritmul djkstra
void djkstra(TGL *g, float *dist, int *vis, int *parents, int *dep) {
  int node;
  float scor = 0;
  for (int i = 0; i< g->n; i++) {
    // determinare nod cu distanta cea mai scurta
    node=det_min_dist(dist, vis, g->n);
    // marcare nod ca vizitat
    vis[node]=1;
    AArc L = g->x[node];
    // parcurgere lista de noduri adiacente
    while((L)) {
        // calculare scor
        scor = (1.0 * L->c)/dep[L->d];
        // atribuire distanta cea mai scurta
        if(vis[(L)->d] == 0 && dist[node] + scor < dist[(L)->d]) {
            dist[(L)->d] = scor + dist[node];
            // mamorare drum in vector de tati
            parents[L->d] = node;
        }

      L=L->urm;
    }
  }
}

// determina costul drumului parcurgand lista de noduri
// corespunzatoare drumului
int cost_drum(TGL *G, TLista *L) {
    int s = 0;
    TLista *p;
    p = L->urm;
    int src, dest;
    src = L->info;
    AArc nod;
    while (p) {
        // cautare nod dest. in lista de adiacenta a sursei
        nod = G->x[src];
        dest = p->info;
        while (nod) {
            if (nod->d == dest) {
                s += nod->c; // insumare cost
                break;
            }
            nod = nod->urm;
        }
        src = p->info; // sursa urmatoare este destinatia curenta
        p = p->urm;
    }
    return s;
}

// determinare adancime minima
int depth_min(TLista *L, int *dep) {
    TLista *p = L->urm;
    int min = 100;
    while (p->urm) {
        if (dep[p->info] < min)
            min = dep[p->info];
        p = p->urm;
    }
    return min;
}

// verificare existenta drum de la corabie la insula
int verif_d_cor_ins(int *parents, int N) {
    int t = 0; // se pleaca de la insula
    int cor_ins = 0;
        for (int i = 0; i < N; i++) {
            t = parents[t];
            if (t == 1) {
                cor_ins = 1; // s-a gasit drum
                break;
            }
            if (t == -1) // s-a incheiat parcurgearea nodurilor
                break;
        }
    return cor_ins;
}

// verificare existenta drum de la insula la corabie
int verif_d_ins_cor(int *parents, int N, TLista **L) {
    int ins_cor = 0; 
    int t = 1;  // se pleaca de la corabie
    TLista *aux;
    // drumul este stocat in lista L
    for (int i = 0; i < N; i++) {
        aux = AlocaElLista(t); // adaugare element in lista
        aux->urm = (*L);
        (*L) = aux;
        t = parents[t];
        if (t == 0) {
            ins_cor = 1; // s-a gasit drum
            break;
        }
        if (t == -1) // s-a incheiat parcurgerea nodurilor
            break;
    }
    
    // adaugare Insula in lista
    aux = AlocaElLista(0);
    aux->urm = (*L);
    (*L) = aux;
    return ins_cor;
}

// scrie in fisierul de iesire datele cerute
void write_in_file(FILE *fout, TGL *G, TLista *L, int masa, int *dep) {
    TLista *aux = L;
    // afisare drum
    while (aux) {
        if (aux->info == 0){
            fprintf(fout, "Insula ");
        } else {
            if (aux->info == 1)
                fprintf(fout, "Corabie \n");
            else
                fprintf(fout, "Nod_%d ", aux->info);
        }
        aux = aux->urm;
    }
    // afisare cost drum
    fprintf(fout, "%d\n", cost_drum(G,L));
    // adancimea minima
    int minad = depth_min(L, dep);
    fprintf(fout, "%d\n", minad);
    // numarul de drumuri
    fprintf(fout, "%d\n", masa/minad);
}