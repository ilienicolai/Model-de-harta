/* NICOLAI Ilie - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>

typedef struct celarc 
{ 
    int d;           /* destinatie arc */
    int c;            /* cost arc */
    struct celarc *urm; /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct 
{ 
    int n;     /* numar noduri */
    AArc* x;    /* vector adrese liste arce */
} TGL;

typedef struct lista
{
    int info;
    struct lista *urm;
}TLista;

TGL* AlocG(int nr);
void Citire_Harta_Task_1(TGL *G, char **locuri, FILE *fin, int M);
void DistrG(TGL** ag);
void Afisare_Harta_1(TGL * g, char **locuri);
void arbprim(TGL *g, int *dist, int *vis);
TLista *AlocaElLista(int suma);
void AdElLista(TLista **L, int suma);
void Afisare_Harta_2(TGL * g);
void Citire_Harta_Task_2(TGL *G, int M, FILE *fin);
void citire_adancimi(int *dep, int N, FILE *fin);
int mindist(int *dist, int *vis, int n);
void djkstra(TGL *g, float *dist, int *vis, int *parents, int *dep);
int cost_drum(TGL *G, TLista *L);
int depth_min(TLista *L, int *dep);
int verif_d_cor_ins(int *parents, int N);
int verif_d_ins_cor(int *parents, int N, TLista **L);
void ElibLista(TLista *L);
void write_in_file(FILE *fout, TGL *G, TLista *L, int masa, int *dep);
void elibmat(char **locuri, int N);