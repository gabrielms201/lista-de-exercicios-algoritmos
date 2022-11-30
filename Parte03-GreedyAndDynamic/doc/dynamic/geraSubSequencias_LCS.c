#include <stdio.h>
/*
Gerar todas as sequencias distintas de uma sequencia
A partir da sequência a[1..n] podemos ter 2^n – 1 subsequências distintas,
Se a[1..3]=(1, 2, 3) temos
1, 2, 3, 1 2, 1 3, 2 3, 1 2 3.
para isso basta remover alguns elementos da seqquencia mas não alterando a ordem.
*/

// variavel global
int seq=1;

// declaracao de funcoes
//algoritmo sequencias(a[1..n], i, s[1..n])
void SubSequencias(char X[], int n, char s[], int i, int j);
void imprima( char v[], int n );

int main(){

    char X[] = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
    char s[] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};

    SubSequencias(X,7,s, 0, 0);
}
// gera SubSequencias
void SubSequencias(char X[], int n, char s[], int i, int j){

    for(j; j < n; j++){
        s[i] = X[j];
        imprima(s,i);
        SubSequencias(X, n, s,i+1, j+1);
    }

}
void imprima( char v[], int n ){
    int i;
    printf("%3d= ",seq++);

    for( i=0; i <= n; i++)
        printf("%c ",v[i]);

    printf("\n");

}

