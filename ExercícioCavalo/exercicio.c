#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {
	int v;   //linha
	int w;   //coluna;
}Aresta;

typedef struct Grafo{
	int V;  //quantidade de vértices;
	int E;  //quantidade de arestas;
   int **adj; //matriz
}Grafo;

typedef struct itemLista
{
    struct itemLista *prox;
    Aresta vertice;
}item;

item *cria_fila();
item *enfileira(item *cabeca, Aresta vertice);
Aresta desenfileira(item *le);

int ConverteLetra(char L);

Grafo *InicializaGrafo(int v);
int **InicializaMatriz (int linhas, int colunas, int valor);
void InsereArestaGrafo(Grafo *G, Aresta E);
void ImprimeGrafo(Grafo *G);
Aresta RetornaAresta (int v, int w);
void LimpaGrafo(Grafo *G);
void CaminhosPossiveis(Grafo *G, Aresta I);
int BFS(Grafo *G, Aresta inicio, Aresta destino);


int main(){
   Grafo *grafo;
   Aresta inicio;
   Aresta final;

   int n;

   scanf("%d", &n);

   grafo = InicializaGrafo(8);

   for(int i=0; i<n; i++){
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

		CaminhosPossiveis(grafo, inicio);

		ImprimeGrafo(grafo);

		printf("\n\n");

		LimpaGrafo(grafo);
   }

   return 0;
}

item *cria_fila(){
    item *cabeca = malloc(sizeof(item));
    cabeca->prox = cabeca;

    return cabeca;
}

item *enfileira(item *cabeca, Aresta vertice){
    item *novo = malloc(sizeof(item));
    if(novo){
        novo-> prox = cabeca->prox;
        cabeca->prox = novo;
        cabeca->vertice = vertice;
        return novo;
    }
    else{
        printf("Não foi possível alocar uma nova célula.\n");
        return;
    }
    //Chamada -- le = enfileira(le, numero);
}

Aresta desenfileira(item *le){
    item *removido = le->prox;
    Aresta vertice;

    removido->prox = le->prox;
    le->prox = removido->prox;
    vertice = removido->vertice;
    free(removido);
    return vertice;
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
	int **matrix = malloc(linhas * (sizeof(int*)));  //Alocando as linhas

	for(int i = 0; i < linhas; i++)
		matrix[i] = malloc(colunas * sizeof(int*));   //Alocando as colunas

	for (int i = 0; i < linhas; i++)
		for(int j = 0; j < colunas; j++)
			matrix[i][j] = valor;

	return matrix;
}

void InsereArestaGrafo(Grafo *G, Aresta E){
	int v = E.v;
	int w = E.w;

	//Se a aresta não foi inserida antes, vamos incrementar a quantidade de arestas	
	if(G->adj[v][w] == 0){
		G->E++;
	}

	//Se for um grafo não-direcionado, vamos preencher ambos os vértices.
	G->adj[v][w] = 1;

	//printf("M[%d][%d]=%d", v , w, G->adj[v][w]);
	
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

void CaminhosPossiveis(Grafo *G, Aresta I){
	//Verificar se não extrapola a matriz
	//Verificar se o vizinho já foi visitado

	// int v;   //linha
	// int w;   //coluna;

	//Se os vizinhos do vértice extrapolam a matriz ou todos já foram visitados, sai

	//Movimento 1
	if(I.v - 2 >= 0 && I.w - 1 >= 0){
		if(G->adj[I.v-2][I.w-1] == 0){
			G->adj[I.v-2][I.w-1] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v-2, I.w-1));
		}
	}

	//Movimento 2
	if(I.v - 1 >= 0 && I.w - 2 >= 0){
		if(G->adj[I.v-1][I.w-2] == 0){
			G->adj[I.v-1][I.w-2] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v-1, I.w-2));
		}
	}

	//Movimento 3
	if(I.v - 2 >= 0 && I.w + 1 <= 7){
		if(G->adj[I.v-2][I.w+1] == 0){
			G->adj[I.v-2][I.w+1] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v-2, I.w+1));
		}
	}	
	
	//Movimento 4
	if(I.v - 1 >= 0 && I.w + 2 <= 7){
		if(G->adj[I.v-1][I.w+2] == 0){
			G->adj[I.v-1][I.w+2] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v-1, I.w+2));
		}
	}	
		
	//Movimento 5
	if(I.v + 1 <= 7 && I.w - 2 >= 0){
		if(G->adj[I.v+1][I.w-2] == 0){
			G->adj[I.v+1][I.w-2] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v+1, I.w-2));
		}
	}	

	//Movimento 6
	if(I.v + 2 <= 7 && I.w - 1 >= 0){
		if(G->adj[I.v+2][I.w-1] == 0){
			G->adj[I.v+2][I.w-1] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v+2, I.w-1));
		}
	}	

	//Movimento 7
	if(I.v + 2 <= 7 && I.w + 1 <= 7){
		if(G->adj[I.v+2][I.w+1] == 0){
			G->adj[I.v+2][I.w+1] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v+2, I.w+1));
		}
	}	

	//Movimento 8
	if(I.v + 1 <= 7 && I.w + 2 <= 7){
		if(G->adj[I.v+1][I.w+2] == 0){
			G->adj[I.v+1][I.w+2] = 1;
			// CaminhosPossiveis(G, RetornaAresta(I.v+1, I.w+2));
		}
	}	
}

int BFS(Grafo *G, Aresta inicio, Aresta destino){

}