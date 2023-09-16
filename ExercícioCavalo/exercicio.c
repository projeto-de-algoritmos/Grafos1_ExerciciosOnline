#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {
	int v;   //vértice v
	int w;   //vértice w;
}Aresta;

typedef struct Grafo{
	int V;  //quantidade de vértices;
	int E;  //quantidade de arestas;
   int **adj; //matriz
}Grafo;

Grafo *InicializaGrafo(int v);
void CaminhosPossiveis(Grafo *G, Aresta I);
Aresta RetornaAresta (int v, int w);
void ImprimeGrafo(Grafo *G);
int **InicializaMatriz (int linhas, int colunas, int valor);
void InsereArestaGrafo(Grafo *G, Aresta E);
int ConverteLetra(char L);

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
   }
   
   ImprimeGrafo(grafo);

   return 0;
}

void ImprimeGrafo(Grafo *G){
	for(int i =0;i<8;i++){
		for(int j=0; j<8;j++){
			printf("%d ", G->adj[i][j]);
		}
		printf("\n");
	}
}

int ConverteLetra(char L){
	return L - 97;
}

void CaminhosPossiveis(Grafo *G, Aresta I){

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
	G->adj[w][v] = 1;

	//printf("M[%d][%d]=%d", v , w, G->adj[v][w]);
	
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


Aresta RetornaAresta(int v, int w){
	Aresta E;

	E.v = v;
	E.w = w;

	return E;
}