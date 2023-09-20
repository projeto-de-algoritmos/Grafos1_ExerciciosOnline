#include <stdlib.h>
#include <stdio.h>

//Estrutura da Aresta (RetornaAresta)
typedef struct Aresta
{
    int v; //vértice v
    int w; //vértice w
}Aresta;



//Estrutura do nó (node)
typedef struct itemLista{
    struct itemLista *next; 
    int vertice; //vértice v
    int visitado;
}item;

typedef item *link; //Link é um ponteiro para nó

//Estrutura do Grafo
typedef struct Grafo{
    int V; //quantidade de vértices
    int E; //quantidade de arestas
    link *adj; //array de ponteiros para nós
}Grafo;

Aresta RetornaAresta(int v, int w);           //Função que retorna uma aresta
link Enfileira (int v, item *next);           //Função que retorna um elemento da lista

Grafo *InicializaGrafo(int v);                //Função que inicializa o grafo
void InsereArestaGrafo(Grafo *G, Aresta e);   //Função que insere aresta no grafo
void ImprimeGrafo(Grafo *G);

void DFS_visit(Grafo *G, link t);
void DFS (Grafo *G);

int main(){
    
    int qtdVertices, posicaoMenino;
    scanf("%d %d ", &qtdVertices, &posicaoMenino);
    Grafo *G = InicializaGrafo(qtdVertices+1);

    for(int i = 1; i< qtdVertices; i++){
        int v, w;
        scanf("%d %d", &v, &w);
        InsereArestaGrafo(G, RetornaAresta(v, w));
    }

    DFS(G);
    // ImprimeGrafo(G);
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
        for(link t = G->adj[v]; t != NULL; t = t->next){
            t->visitado = 0;
        }
    }

    return G;
}

void InsereArestaGrafo(Grafo *G, Aresta e){
    int v = e.v;
    int w = e.w;

    G->adj[v] = Enfileira(w, G->adj[v]);
    G->adj[w] = Enfileira(v, G->adj[w]);

    link t = G->adj[v];
    t->visitado = 0;

    t = G->adj[w];
    t->visitado = 0;

    G->E++;
}

void ImprimeGrafo(Grafo *G){
    int v;
    link t;

    for (v = 0; v < G->V; v++){
        printf("[%d] --> ", v);
        for(t = G->adj[v]; t != NULL; t = t->next){
            printf("%d(%d) --> ", t->vertice, t->visitado);
        }
        printf("NULL\n");
    }
    
}

void DFS_visit(Grafo *G, link t){
    t->visitado = 1;
    for(link w = G->adj[t->vertice]; w != NULL; w = w->next){
        if(w->visitado!=1){         
            DFS_visit(G, w);
        }
    }
}

void DFS (Grafo *G){
    for (int v = 0; v < G->V; v++){
        for(link t = G->adj[v]; t != NULL; t = t->next){
            if(t->visitado!=1){         
                DFS_visit(G, t);
            }
        }
    }
}