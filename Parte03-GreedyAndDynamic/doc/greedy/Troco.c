#include <stdio.h>
#include <stdlib.h> // calloc

int * Troco( int C[], int N, int valor);
int main(){
    int C[] = {100, 50, 25, 10, 1};
    int N = 5;

    int *S = Troco(C, N, 37);
    if( S != NULL ){
        for(int i=0; i < N; i++)
            printf("%d ", S[i]);
        free(S);
    }
    return 0;
}
int * Troco( int C[], int N, int valor){
    // S e a solução com as moedas usadas
    // S <- 0
    int *S = (int*)calloc(N,sizeof(int)); // int S[N]
    // soma <- 0
    int soma = 0, i=0;
    // enquanto  soma < valor E C ≠ {} faça
    while( soma < valor && i < N ){
        // x <- moeda de maior valor em C
        int x = C[i];
        // se soma + x  <= valor então
        if( soma + x <= valor){
            // soma <- soma + x;
            soma = soma + x;
            // S <- S U {x}
            S[i]++; // S[i] = S[i]+1
        }
        else
            // C <- C – {x}
            i++;

    }
    // se soma = valor então
    if( soma == valor)
	   // retornar S
	   return S;
	else{
       // retornar "Não encontrei solução"
       free(S);
 	   return NULL;

	}
}


