/* NICOLAI Ilie - 313CB */
#include "structs.h"

int main(int argc, char *argv[]) {
    // deschidere fisiere
    FILE *fin = fopen("tema3.in", "r");
    FILE *fout = fopen("tema3.out", "w");
    int N; // numarul de noduri
    int M; // numarul de muchii
    fscanf(fin, "%d", &N);
    fscanf(fin, "%d", &M);
    TGL *G = NULL;
    TLista *L = NULL;
    // alocare graf
    G = AlocG(N);
    if (!strcmp(argv[1], "1")) {    // CERINTA 1
        char **locuri;  // matrice de denumiri
        // alocare matrice de denumiri
        locuri = (char **)calloc((N + 1), sizeof(char *));
        if (!locuri) {
            printf("error1\n");
        }
        for (int i = 0; i <= N; i++) {
            locuri[i] = (char *)calloc(15, sizeof(char));
            if (!locuri[i]) {
                printf("error2\n");
                for (int j = 0; j < i; j++)
                    free(locuri[j]);
                free(locuri);
            }
        }
        // citirea hartii
        Citire_Harta_Task_1(G, locuri, fin, M);

        // alocare vectori de distante si visited
        int *distances = (int *)malloc((G->n+1) * sizeof(int));
        int *visited = (int*)calloc(G->n+1,sizeof(int));
        // initializare distances cu valoarea maxima a int
        for (int i=0; i<=G->n;i++)
            distances[i]=__INT_MAX__;
        // numarare componente conexe
        // determinare cost pentru fiecare componenta
        int p=1;
        int suma = 0;
        for (int i = 1; i <= G->n; i++) {
            // apelare algoritm prim pentru fiecare componenta
            if (distances[i] == __INT_MAX__) {
                distances[i] = 0;
                arbprim(G, distances, visited);
                p++;
                suma = 0;
                for (int j = 1; j <= G->n; j++) {
                    if (visited[j] == 1) {
                        // determinare cost total pt. componenta
                        suma += distances[j];
                        // marcare zona parcursa
                        visited[j] = p;
                    }
                }
                // adaugare suma in lista sortata
                AdElLista(&L, suma);
            }
        }
        // afisare numar de zone despartite de ape
        fprintf(fout, "%d\n", p-1);
        // afisare costuri totale
        TLista *aux = L;
        while (aux) {
            fprintf(fout, "%d\n", aux->info);
            aux = aux->urm;
        }
        // eliberare memorie
        elibmat(locuri, G->n);
        ElibLista(L);
        DistrG(&G);
        free(distances);
        free(visited);
        fclose(fin);
        fclose(fout);
    } else {    // CERINTA 2
        int masa = 0;   // masa comorii
        // citire harta
        Citire_Harta_Task_2(G, M, fin);
        // alocare voctor de adancimi
        int *dep = (int *)calloc(N, sizeof(int));
        // alocare vector de distante
        float *distances = (float *)malloc((G->n) * sizeof(float));
        // alocare vector de vizitati
        int *visited = (int*)calloc(G->n, sizeof(int));
        // alocare vector de parinti
        int *parents = (int*)calloc(G->n, sizeof(int));
        // initializare vectori
        for (int i=0; i < G->n;i++) {
            parents[i]=-1;
            distances[i]=__INT_MAX__;
        }
        // citire adancimi
        citire_adancimi(dep, N, fin);
        // citire masa comoara
        fscanf(fin, "%d", &masa);
        // cautare drum de la corabie la insula
        distances[1]=0;
        djkstra(G, distances, visited, parents, dep);
        int t = 0;
        int cor_ins = verif_d_cor_ins(parents, G->n); // verificare daca exista
        if (cor_ins == 0) {     // daca nu se gaseste drum
            fprintf(fout, "Echipajul nu poate ajunge la insula\n");
            DistrG(&G);
            free(distances);
            free(parents);
            free(dep);
            free(visited);
            fclose(fin);
            fclose(fout);
            return 0;
        }
        // restaurare vectori de informatii
        for (int i=0; i < G->n;i++) {
            parents[i] = -1;
            visited[i] = 0;
            distances[i] = __INT_MAX__;
        }
        // cautare drum de la insula la corabie
        distances[0]=0;
        djkstra(G, distances, visited, parents, dep); 
        // verificare daca exista
        int ins_cor = verif_d_ins_cor(parents, G->n, &L);
        TLista *aux;
        if (ins_cor == 0) {     // daca nu exista drum
            fprintf(fout, "Echipajul nu poate transporta comoara inapoi la corabie\n");
        } else {    // daca exista
            // determinare si scriere in fisier a informatiilor
            write_in_file(fout, G, L, masa, dep);
        }
        // eliberare memorie
        DistrG(&G);
        free(distances);
        free(parents);
        free(dep);
        free(visited);
        ElibLista(L);
        fclose(fin);
        fclose(fout);
    }
    return 0;
}