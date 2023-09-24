#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Key(A) (A.nome) 
#define less(A,B) (Key(A) < Key(B)) 
#define lesseq(A,B) ((A) <= (B))
#define exch(A,B) { Item t; t=A;A=B;B=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }

typedef struct node{
    int v; //vértice v
    struct node *next; 
}node;

typedef node *link; 

typedef struct Edge
{
    int v; 
    int w; 
}Edge;


typedef struct graph{
    int V; 
    int E; 
    link *adj; 
}Graph;

Edge EDGE(int v, int w);               
link NEW (int v, node *next);        
Graph *GRAPHInit(int v);                
void GRAPHInsert(Graph *G, Edge e);     
void dfsR(Graph *G, Edge e);            
void GRAPHSearch(Graph *G);          

typedef struct animal{
    char nome[31];
    int numero_Vertice;
}animal;

typedef animal Item;

int separa(Item *V,int l,int r);
void quicksort(Item *v, int l, int r);
void quicksortM3(Item *v, int l, int r);
int busca_binaria(animal conjunto[], int tamanho, char *buscado);

static int seres_cadeia, pre[5005];

int main(){
    Graph *Grafo;
    int C, R, maior_cadeia;
    animal *dados;
    animal elemento_A, elemento_B;
    int indice_A, indice_B;

    while (scanf("%d %d", &C, &R) != EOF && (C + R)){
        Grafo = GRAPHInit(C);
        dados = malloc(sizeof(animal) * C);
    
        for (int i = 0; i < C; i++){
            scanf(" %s", elemento_A.nome);
            elemento_A.numero_Vertice = i;

            dados[i] = elemento_A;
        }

        quicksortM3(dados,0, C-1);

        for (int i = 0; i < R; i++){
            scanf(" %s %s", elemento_A.nome, elemento_B.nome);
            
            indice_A = busca_binaria(dados, C, elemento_A.nome);
            indice_B = busca_binaria(dados, C, elemento_B.nome);

            GRAPHInsert(Grafo, EDGE(indice_A, indice_B));
        }

        GRAPHSearch(Grafo);
        free(Grafo);
        free(dados);
    }

    return 0;
}

Edge EDGE(int v, int w){
    Edge E;
    
    E.v = v;
    E.w = w;

    return E;    
}

link NEW (int v, node *next){
    link x = malloc(sizeof(*x));

    if(x){
        x->next = next;
        x->v = v;
        return x;
    }

    else{
        return NULL;
    }
}

Graph *GRAPHInit(int v){
    Graph *G = malloc(sizeof(G));
    G->V = v;
    G->E = 0;
    G->adj = malloc(v * sizeof(link));

    for (v = 0; v < G->V; v++){
        G->adj[v] = NULL;
    }

    return G;
}

void GRAPHInsert(Graph *G, Edge e){
    int v = e.v;
    int w = e.w;

    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[w]);

    G->E++;
}

void dfsR(Graph *G, Edge e){
    int t, w = e.w;
    link l;

    pre[w] = seres_cadeia++;

    for(l = G->adj[w]; l != NULL; l = l->next){
        t = l->v;

        if(pre[t] == -1)
            dfsR(G, EDGE(w, t));
    }
}   

void GRAPHSearch(Graph *G){
    int v, conexos = 0;
    seres_cadeia = 0;
    int maior_cadeia;

    for(v = 0; v < G->V; v++){
        pre[v] = -1;
    }

    for(v = 0; v < G->V; v++){
        seres_cadeia = 0;

        if(v == 0){
            maior_cadeia = 0;
        }
        if(pre[v] == -1){
            seres_cadeia = 0;
            dfsR(G, EDGE(v, v));
            
            if(seres_cadeia > maior_cadeia){
                maior_cadeia = seres_cadeia;
            }
        }
    }
    printf("%d\n", maior_cadeia);
}         

int separa(Item *V,int l,int r){
  Item c=V[r];
  int j=l;

  for(int k=l;k<r;k++)
    if(strcmp(V[k].nome,c.nome) < 0){
      exch(V[k],V[j]);
      j++;
    }

  exch(V[j],V[r]);
  return j;
}

void quicksort(Item *v, int l, int r){
    int j;
    if(r <= l) return;

    j = separa(v, l ,r);

    quicksort(v, l, j-1);
    quicksort(v, j+1, r);
}

void quicksortM3(Item *v, int l, int r){
    int j;
    if(r <= l) return;

    cmpexch(v[(l+2) / 2], v[r]);
    cmpexch(v[l], v[(l+r) / 2]);
    cmpexch(v[r], v[(l+r) / 2]);

    j = separa(v, l ,r);

    quicksort(v, l, j-1);
    quicksort(v, j+1, r);
}

int busca_binaria(animal conjunto[], int tamanho, char *buscado){
    int inicio = -1, fim = tamanho;

    while(inicio < fim - 1){
        int meio = (inicio + fim) / 2;

        if(strcmp(conjunto[meio].nome, buscado) == 0){
            return conjunto[meio].numero_Vertice;
        }

        if(strcmp(conjunto[meio].nome, buscado) < 0){
            inicio = meio;
        }
        else{
            fim = meio;
        }
    } 
    return -1;
}
