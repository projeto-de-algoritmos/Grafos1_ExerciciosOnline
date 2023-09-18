#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {
	int v;  
	int w;   
}Aresta;

typedef struct Grafo{
	int V;  
	int E;  
   int **adj; 
}Grafo;

typedef struct itemLista {
    struct itemLista *next;
    Aresta vertice;
} item;

typedef struct Fila {
    item *front;
    item *rear;
} Fila;

Fila *cria_fila();
void enfileira(Fila *fila, Aresta valor);
Aresta desenfileira(Fila *fila);
void libera_fila(Fila *fila);
void imprime_fila(Fila *fila);

int ConverteLetra(char L);

Grafo *InicializaGrafo(int v);
int **InicializaMatriz (int linhas, int colunas, int valor);
void InsereArestaGrafo(Grafo *G, Aresta E);
void ImprimeGrafo(Grafo *G);
Aresta RetornaAresta (int v, int w);
void LimpaGrafo(Grafo *G);

int BFS(Grafo *G, Aresta inicio, Aresta destino);


int main(){
   Grafo *grafo;
   Aresta inicio;
   Aresta final;

   int n;

   scanf("%d", &n);

   grafo = InicializaGrafo(8);

   for(int i=0; i<n; i++){
	    Fila *fila = cria_fila();
		char w;
		int v;	

		scanf(" %c", &w);
		scanf("%d", &v);

		inicio.w = ConverteLetra(w);
		inicio.v = v - 1;
		
		InsereArestaGrafo(grafo, inicio);

		scanf(" %c", &w);
		scanf("%d", &v);

		final.w = ConverteLetra(w);
		final.v = v - 1;

   		InsereArestaGrafo(grafo, final);

		printf("%d\n", BFS(grafo, inicio, final));
        
		LimpaGrafo(grafo);
		libera_fila(fila);
   }

   return 0;
}

void imprime_fila(Fila *fila) {
    if (fila->front == NULL) {
        return;
    }

    item *atual = fila->front;
    while (atual != NULL) {
        printf("%d %d -> ", atual->vertice.v, atual->vertice.w);
        atual = atual->next;
    }

    printf("\n");
}


Fila *cria_fila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->front = fila->rear = NULL;
    return fila;
}

void enfileira(Fila *fila, Aresta valor) {
    item *novo = malloc(sizeof(item));
    novo->vertice = valor;
    novo->next = NULL;

    if (fila->rear == NULL) {
        fila->front = fila->rear = novo;
        return;
    }

    fila->rear->next = novo;
    fila->rear = novo;
}

Aresta desenfileira(Fila *fila) {
    if (fila->front == NULL) {
        printf("A fila está vazia.\n");
        return RetornaAresta(-1,-1); 
    }

    item *temp = fila->front;
    Aresta valor = temp->vertice;

    fila->front = fila->front->next;

    if (fila->front == NULL) {
        fila->rear = NULL;
    }

    free(temp);
    return valor;
}

void libera_fila(Fila *fila) {
    while (fila->front != NULL) {
        item *temp = fila->front;
        fila->front = fila->front->next;
        free(temp);
    }
    free(fila);
}

int ConverteLetra(char L){
	return L - 97;
}

Grafo *InicializaGrafo(int v){
	Grafo *G = malloc(sizeof(G));  
	G->V = v;  
	G->E = 0;  
	G->adj = InicializaMatriz(v, v, 0);

	return G;  
}

int **InicializaMatriz (int linhas, int colunas, int valor){
	int **matrix = malloc(linhas * (sizeof(int*)));  

	for(int i = 0; i < linhas; i++)
		matrix[i] = malloc(colunas * sizeof(int*));   

	for (int i = 0; i < linhas; i++)
		for(int j = 0; j < colunas; j++)
			matrix[i][j] = valor;

	return matrix;
}

void InsereArestaGrafo(Grafo *G, Aresta E){
	int v = E.v;
	int w = E.w;

	if(G->adj[v][w] == 0){
		G->E++;
	}

	G->adj[v][w] = 1;	
}

void ImprimeGrafo(Grafo *G){
	for(int i =0;i<8;i++){
		for(int j=0; j<8;j++){
			printf("%d ", G->adj[i][j]);
		}
		printf("\n");
	}
}

Aresta RetornaAresta(int v, int w){
	Aresta E;

	E.v = v;
	E.w = w;

	return E;
}

void LimpaGrafo(Grafo *G){
	for(int i =0;i<8;i++){
		for(int j=0; j<8;j++){
			G->adj[i][j] = 0;
		}
	}
}

int BFS(Grafo *G, Aresta inicio, Aresta destino) {
    int **matrizAuxiliar = InicializaMatriz(8, 8, -1);

    Fila *fila = cria_fila();

    enfileira(fila, inicio);
    matrizAuxiliar[inicio.v][inicio.w] = 0;

    while (fila->front != NULL) {
        Aresta verticeAtual = desenfileira(fila);

        int v = verticeAtual.v;
        int w = verticeAtual.w;

        if (v == destino.v && w == destino.w) {
            return matrizAuxiliar[v][w]; 
        }

        // Movimento 1
        if (v - 2 >= 0 && w - 1 >= 0 && matrizAuxiliar[v-2][w-1] == -1) {
            matrizAuxiliar[v-2][w-1] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v-2, w-1));
        }

        // Movimento 2
        if (v - 1 >= 0 && w - 2 >= 0 && matrizAuxiliar[v-1][w-2] == -1) {
            matrizAuxiliar[v-1][w-2] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v-1, w-2));
        }

        // Movimento 3
        if (v - 2 >= 0 && w + 1 <= 7 && matrizAuxiliar[v-2][w+1] == -1) {
            matrizAuxiliar[v-2][w+1] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v-2, w+1));
        }

        // Movimento 4
        if (v - 1 >= 0 && w + 2 <= 7 && matrizAuxiliar[v-1][w+2] == -1) {
            matrizAuxiliar[v-1][w+2] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v-1, w+2));
        }

        // Movimento 5
        if (v + 1 <= 7 && w - 2 >= 0 && matrizAuxiliar[v+1][w-2] == -1) {
            matrizAuxiliar[v+1][w-2] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v+1, w-2));
        }

        // Movimento 6
        if (v + 2 <= 7 && w - 1 >= 0 && matrizAuxiliar[v+2][w-1] == -1) {
            matrizAuxiliar[v+2][w-1] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v+2, w-1));
        }

        // Movimento 7
        if (v + 2 <= 7 && w + 1 <= 7 && matrizAuxiliar[v+2][w+1] == -1) {
            matrizAuxiliar[v+2][w+1] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v+2, w+1));
        }

        // Movimento 8
        if (v + 1 <= 7 && w + 2 <= 7 && matrizAuxiliar[v+1][w+2] == -1) {
            matrizAuxiliar[v+1][w+2] = matrizAuxiliar[v][w] + 1;
            enfileira(fila, RetornaAresta(v+1, w+2));
        }
    }

    return -1; 
}