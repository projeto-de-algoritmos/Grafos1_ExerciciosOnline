#include <stdlib.h>
#include <stdio.h>

//Estrutura da Aresta (RetornaAresta)
typedef struct Aresta
{
    int v; //vértice v
    int w; //vértice w
}Aresta;

//Estrutura do Grafo
typedef struct Grafo{
    int V; //quantidade de vértices
    int E; //quantidade de arestas
    link *adj; //array de ponteiros para nós
}Grafo;

//Estrutura do nó (node)
typedef struct itemLista{
    struct itemLista *next; 
    int vertice; //vértice v
}item;

typedef item *link; //Link é um ponteiro para nó

Aresta RetornaAresta(int v, int w);           //Função que retorna uma aresta
link Enfileira (int v, item *next);           //Função que retorna um elemento da lista

Grafo *InicializaGrafo(int v);                //Função que inicializa o grafo
void InsereArestaGrafo(Grafo *G, Aresta e);   //Função que insere aresta no grafo
void ImprimeGrafo(Grafo *G);

int main(){

    return 0;
}

Aresta RetornaAresta(int v, int w){
    Aresta E;
    
    E.v = v;
    E.w = w;

    return E;    
}

link Enfileira (int v, item *next){
    link x = malloc(sizeof(*x));

    if(x){
        x->next = next;
        x->vertice = v;
        return x;
    }

    else{
        return NULL;
    }
}

Grafo *InicializaGrafo(int v){
    Grafo *G = malloc(sizeof(G));
    G->V = v;
    G->E = 0;
    G->adj = malloc(v * sizeof(link));

    for (v = 0; v < G->V; v++){
        G->adj[v] = NULL;
    }

    return G;
}

void InsereArestaGrafo(Grafo *G, Aresta e){
    int v = e.v;
    int w = e.w;

    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[w]);

    G->E++;
}

void ImprimeGrafo(Grafo *G){
    int v;
    link t;

    for (v = 0; v < G->V; v++){
        printf("[%d] --> ", v);
        for(t = G->adj[v]; t != NULL; t = t->next){
            printf("%d --> ", t->vertice);
        }
        printf("NULL\n");
    }
    
}