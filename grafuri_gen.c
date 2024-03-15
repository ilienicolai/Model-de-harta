/* NICOLAI Ilie - 313CB */
#include "structs.h"

TGL* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
    TGL* g = (TGL *)malloc(sizeof(TGL));    /* spatiu descriptor */
    if (!g) 
        return NULL;
    g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
    if(!g->x) { 
        free(g); 
        return NULL; 
    }
    g->n = nr;
    return g;
}

// afisare harta CERINTA 1
void Afisare_Harta_1(TGL * g, char **locuri)
{
    AArc l;
    int i;
    for(i = 1; i <= g->n; i++){
        l = g->x[i];
        if(!l)
            printf("%s: - \n", locuri[i]);
        else
            printf("%s: ", locuri[i]);
        for(; l != NULL; l = l->urm)
            printf(" %s (%d)", locuri[l->d], l->c);
        printf("\n");
    }
}

// afisare harta CERINTA 2
void Afisare_Harta_2(TGL * g)
{

    AArc l;
    int i;
    for(i = 0; i < g->n; i++){
        l = g->x[i];
        if(!l) {
            if (i == 0) {
                printf("Insula: - \n");
            } else {
                if (i == 1)
                    printf("Corabie: - \n");
                else {
                    printf("Nod_%d: - \n", i);
                }
            }
        
        } else {
            if (i == 0) {
                printf("Insula: ");
            } else {
                if (i == 1)
                    printf("Corabie: ");
                else {
                    printf("Nod_%d: ", i);
            }
            }

        }
        for(; l != NULL; l = l->urm) {
            if (l->d == 0) {
                printf("Insula (%d) ", l->c);
            } else {
                if (l->d == 1)
                    printf("Corabie (%d) ", l->c);
                else {
                    printf("Nod_%d (%d) ", l->d, l->c);
                }
            }
        }
      
        printf("\n");
  }
}
