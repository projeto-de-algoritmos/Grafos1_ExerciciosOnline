#include <stdlib.h>
#include <stdio.h>

typedef struct Aresta
{
    int v; 
    int w; 
}Aresta;

typedef struct itemLista{
    struct itemLista *next; 
    int vertice; 
    int visitado;
}item;

typedef item *link;

typedef struct Grafo{
    int V; 
    int E; 
    link *adj;
}Grafo;

Aresta RetornaAresta(int v, int w);    
link Enfileira (int v, item *next);          

Grafo *InicializaGrafo(int v);                
void InsereArestaGrafo(Grafo *G, Aresta e);   
void ImprimeGrafo(Grafo *G);

void DFS_visit(Grafo *G, link t, int time);
void DFS (Grafo *G);
int BFS(Grafo *G, int start);

int main(){
    
    int qtdVertices, posicaoMenino;
    scanf("%d %d ", &qtdVertices, &posicaoMenino);
    Grafo *G = InicializaGrafo(qtdVertices+10);

    for(int i = 1; i < qtdVertices; i++){
        int v, w;
        scanf("%d %d", &v, &w);
        InsereArestaGrafo(G, RetornaAresta(v, w));
    }


        int camada = BFS(G, 1);
        camada = (camada - 1) * 2;
        printf("%d", camada);
    
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

int BFS(Grafo *G, int start){
    int *visitado = malloc(G->V * sizeof(int));
    for(int i = 0; i < G->V; i++)
        visitado[i] = 0;

    int *fila = malloc(G->V * sizeof(int));
    int inicio = 0, fim = 0;
    int camadas = -1;

    visitado[start] = 1;
    fila[fim++] = start;

    while (inicio != fim) {
        int v = fila[inicio++];
        if (visitado[v] > camadas)
            camadas = visitado[v];
        
        for (link t = G->adj[v]; t != NULL; t = t->next) {
            int w = t->vertice;
            if (!visitado[w]) {
                visitado[w] = visitado[v] + 1;
                fila[fim++] = w;
            }
        }
    }
    free(visitado);
    free(fila);
    return camadas;
}