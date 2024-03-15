/* NICOLAI Ilie - 313CB */
#include "structs.h"

// alocare element de lista
TLista *AlocaElLista(int info) {
    TLista *aux;
    aux = (TLista *)malloc(sizeof(TLista));
    if (!aux)
        return NULL;
    aux->urm=NULL;
    aux->info = info;
    return aux; 
}

// adaugare element in lista ordonata crescator
void AdElLista(TLista **L, int suma) {
    TLista *aux, *p, *ant = NULL;
    aux = AlocaElLista(suma);   // alocare element
    if (!(*L)) {    // daca lista e vida
        (*L) = aux;
    } else {
        p = (*L);   // parcurgere lista cu retinere anterior
        while (p != NULL && p->info < aux->info ) {
            ant = p;
            p = p->urm;

        }
        if (ant == NULL) {
            aux->urm = (*L);
            (*L) = aux;
        }
        else {
            aux->urm = ant->urm;
            ant->urm = aux;
        }
                    
    } 
}