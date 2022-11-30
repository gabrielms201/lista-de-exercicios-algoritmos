#include <stdio.h>
int Piramide(int P[][5], int i, int j, int N);
int PiramidePD(int P[][5], int S[][5], int N);
int main(void){
    int P[][5] ={{7,0,0,0,0},
                 {3,8,0,0,0},
                 {8,1,0,0,0},
                 {2,7,4,4,0},
                 {4,5,2,6,5}
                 };
    int S[5][5];
    int resposta = Piramide(P,0,0,5);
    printf("\nmaior soma do topo ateh a base usando forca-bruta:%d\n",resposta);

    resposta = PiramidePD(P,S,5);
    printf("\nmaior soma do topo ateh a base usando programcao dinamica:%d\n",resposta);
    printf("\nfim de programa.\n");
    return 0;
}
// forca bruta complexidade O(2^n)
int Piramide(int P[][5], int i, int j, int N){
    // condicao de parada
    if( i == N-1)
        return P[i][j];
    else{
        int Esq = Piramide(P,i+1,j,N);
        int Dir = Piramide(P,i+1,j+1,N);
        if(Esq>Dir)
            return Esq+P[i][j];
        else
            return Dir+P[i][j];
    }
}
// programacao dinamica complexidade O(N^2)
int PiramidePD(int P[][5], int S[][5], int N){
    for( int i=N-1; i>=0; i--){
        for( int j=0; j<=i; j++){
            if( i == N-1)
                S[i][j] = P[i][j];
            else{
                // testa se o filho esquerdo eh
                // maior que o filho direito
                if(S[i+1][j]>S[i+1][j+1])
                    S[i][j] = S[i+1][j]+P[i][j];
                else
                    S[i][j] = S[i+1][j+1]+P[i][j];
            }
        }
    }
    return S[0][0];

}
