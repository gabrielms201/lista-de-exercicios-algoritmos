#include <stdio.h>
#include <stdlib.h> // calloc
// definir um tipo para armazenar uma atividade
typedef struct{
    int s,f;
}TAtividade;
// declara a funcao
TAtividade *selecaoAtividades(TAtividade A[], int N, int *qtd);
void bolha(TAtividade A[], int N);
void imprimeAtividades(TAtividade A[], int N);

int main(){
    TAtividade A[]= {{3,5},{0,6},{5,9},{2,13},{6,10},{3,8},{1,4},{5,7},{12,14}, {8,12},{8,11}};
    //TAtividade A[]= {{4,5},{0,4},{2,3},{1,2}};
    int N=11;
    int qtdSelecionados;
    printf("\nAtividades de Entrada: ");
    imprimeAtividades(A,N);
    TAtividade *S = selecaoAtividades(A, N, &qtdSelecionados);

    // imprime as atividades selecionadas no vetor S[]
    printf("\nAtividades de Selecionadas: ");
    imprimeAtividades(S,qtdSelecionados);

    free(S);

    return 0;
}
TAtividade *selecaoAtividades(TAtividade A[], int N, int  *qtd){
    TAtividade *S = (TAtividade *) calloc(N,sizeof(TAtividade));
    //Ordene as atividades em ordem crescente de término
    bolha(A,N);
    *qtd = 1;
    // S <- {a1}
    S[0] = A[0];
    // i <- 1
    int i = 0;
    // para j de 2 até n faça
    for( int j=1; j<N;j++){
       // se sj >= fi então
       if(A[j].s>=A[i].f){
          // S <- S U {aj}
          S[*qtd] = A[j];
          (*qtd)++;
          // i <- j
          i = j;
       }
    }

    return S;
}

void bolha(TAtividade A[], int N){
    for(int k=1; k < N; k++){
        for( int i=0;i<N-k;i++){
            if(A[i].f>A[i+1].f){
                TAtividade temp = A[i];
                A[i]=A[i+1];
                A[i+1]=temp;
            }
        }
    }
}

void imprimeAtividades(TAtividade A[], int N){
    for(int i=0; i < N;i++)
         printf("s=%d:f=%d ",A[i].s,A[i].f);

}
