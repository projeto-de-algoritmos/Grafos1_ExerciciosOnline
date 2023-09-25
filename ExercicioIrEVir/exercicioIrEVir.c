#include<stdio.h>
#include <stdbool.h>

bool cidade[2001][2001];
bool visitados[2001];
int N, P;
 
void DFS( int vertice );
 
int main(){
 
    scanf(" %d", &N);

    while( N != 0 ){

        scanf(" %d", &P);

        for( int i = 1; i <= N; i++ ){
            visitados[ i ] = false;

            for( int j = 1; j <= N; j++ ){
                cidade[ i ][ j ] = false;
            }
        }
 
        for( int i = 1; i <= P; i++ ){

            int vertice_a, vertice_b, direcao;

            scanf(" %d %d %d", &vertice_a, &vertice_b, &direcao);

            if( direcao == 1 ){
                cidade[ vertice_a ][ vertice_b ] = true; 
            }

            else{
                cidade[ vertice_a ][ vertice_b ] = true; 
                cidade[ vertice_b ][ vertice_a ] = true; 
            }

        }
 
        DFS( 1 );
 
        bool conectado = true;
        for( int i = 1; i <= N; i++ ){
            if( !visitados[ i ] ){
                conectado = false;
            }
        }
 
        if( conectado == true ){
            for( int i = 1; i <= N; i++ ){
                visitados[ i ] = false;
                for( int j = i+1; j <= N; j++ ){
                    if( cidade[ i ][ j ] && cidade[ j ][ i ] ) continue;
                    else if( cidade[ i ][ j ] ){
                        cidade[ j ][ i ] = true; cidade[ i ][ j ] = false;
                    }else if( cidade[ j ][ i ] ){
                        cidade[ i ][ j ] = true; cidade[ j ][ i ] = false;
                    }
                }
             }
 
            DFS( 1 );
        }

        for( int i = 1; i <= N; i++ ){
            if( !visitados[ i ] ){
                conectado = false;
            }
        }
 
        if( conectado ){
           printf("1\n"); 
        } 
        else {
            printf("0\n");
        }
        scanf(" %d", &N);
    }
 
    return 0;
}

void DFS( int vertice ){
    if( visitados[ vertice ] == true ){
        return;
    }

    else{
        visitados[ vertice ] = true;

    for( int i = 1; i <= N; i++ )
        if( cidade[ vertice ][ i ] && !visitados[ i ] ) DFS( i );
    }
}
