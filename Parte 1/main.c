#include <stdio.h>
#include <stdlib.h>

void printar(int v[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", v[i]);
	printf("\n");
}

// Ex 1
// Escreva uma função para inverter a ordem dos elementos de um vetor V[]. Você não pode usar outro vetor como
// área auxiliar.A função deve ter deve ter complexidade O(n), ou seja, o tamanho do vetor V[].

void inverte(int v[], int tamanho)
{
	int i;
	int passos = 0;
	int k = tamanho - 1;
	for (i = 0; i < tamanho / 2; i++)
	{
		int aux = v[i];
		v[i] = v[k];
		v[k] = aux;
		k--;
		passos++;
	}
	printf("%d", passos);
}
// 1 2 3 4 5 6 7 8
// 8 2 3 4 5 6 7 1
// 8 7 3 4 5 6 2 1
// 8 7 6 4 5 3 2 1
// 8 7 6 4 4 3 2 1

//2 Escreva uma função que recebe um vetor A[] e troca de posição seu maior e seu menor elementos.A função deve ter
//deve ter complexidade O(n), ou seja, o tamanho do vetor V[].
void troca(int v[], int tamanho)
{
	int maior = 0;
	int menor = v[0];
	int indexMaior = 0;
	int indexMenor = 0;
	int i;
	for (i = 0; i < tamanho; i++)
	{
		if (v[i] > maior)
		{
			indexMaior = i;
			maior = v[i];
		}
		if (v[i] < menor)
		{
			indexMenor = i;
			menor = v[i];
		}
	}
	int aux = v[indexMaior];
	v[indexMaior] = v[indexMenor];
	v[indexMenor] = aux;
}

// 3 Dado um vetor de n números inteiros, faça uma função para determinar o comprimento de um segmento crescente
//de comprimento máximo.
//Exemplos: Na sequência
//{ 5, 10, 3, 2, 4, 7, 9, 8, 5 } o comprimento do segmento crescente máximo é 4 {2, 4, 7, 9}.
//Na sequência
//{ 10, 8, 7, 5, 2 } o comprimento de um segmento crescente máximo é 1.
//A função deve ter deve ter complexidade O(n), ou seja, o tamanho do vetor
int comprimento(int v[], int tamanho)
{
	int i;
	int streak = 1;
	int maxStreak = 0;
	for (i = 0; i < tamanho - 1; i++)
	{
		if (v[i] < v[i + 1])
			streak++;
		else
		{
			streak = 1;
		}
		if (streak > maxStreak)
			maxStreak = streak;
	}
	return maxStreak;
}

//4   Escreva o algoritmo que recebe um vetor A de tamanho n contendo inteiros e encontra o par de elementos distintos
//a e b do vetor que fazem com que a diferença a - b seja a maior possível.A função deve ter deve ter complexidade
//O(n), ou seja, o tamanho do vetor V[].
// Maior diferenca possivel = maior valor - menor valor
// Maiores valores
void parDeElementos(int v[], int tamanho, int* par)
{
	int maiorValor = 0;
	int menorValor = v[0];
	int maiorDiff = 0;
	int i;
	for (i = 0; i < tamanho; i++)
	{
		if (v[i] > maiorValor)
			maiorValor = v[i];
		if (v[i] < menorValor)
			menorValor = v[i];
	}
	maiorDiff = maiorValor - menorValor;
	par[0] = maiorValor;
	par[1] = menorValor;
}


//5Escreva uma função que receba dois vetores(A[] e B[]) já ordenados em ordem crescente e ambos possuem o mesmo
//tamanho.A sua função imprime a INTERSECÇÃO entre os dois vetores, ou seja, os elementos em comum entre os
//vetores A[] e B[].Considere que os vetores não contêm valores duplicados.A função deve ter deve ter complexidade
//O(n), ou seja, o tamanho do vetor A[] e do vetor B[].
void inter(int v1[], int v2[], int tamanho)
{
	int i = 0;
	int j = 0;
	int count;
	while (j < tamanho && i < tamanho)
	{
		if (v1[i] == v2[j])
		{
			printf("%d,", v1[i]);
			i++;
		}
		if (v1[i] < v2[j]) i++;
		else j++;
	}
}
//6 Repita o exercício anterior, agora deve ser impresso os elementos que estão em A[] mas não estão em B[].A função
//deve ter deve ter complexidade O(n), ou seja, o tamanho dos vetores.
void diferencaVetores(int v1[], int v2[], int tamanho)
{
	int i = 0;
	int j = 0;
	int count = -1;
	while (j < tamanho && i < tamanho)
	{
		if (v1[i] == v2[j])
		{
			i++;
			j++;
		}
		if (v1[i] < v2[j])
		{
			printf("%d,", v1[i]);
			i++;
		}
		else j++;
		count++;
	}
}
// 7) Escreva uma função que receba dois vetores (A[] e B[]), com n e m elementos, respectivamente. Os vetores estão
// ordenados em ordem crescente, a função aloca um vetor C[], exatamente com soma dos tamanhos de A e B, e
// intercala os elementos de A[] e B[] em C[], de forma que o vetor C[] fique em ordem crescente.A função deve ter
// deve ter complexidade O(n + m), ou seja, a soma dos tamanho dos vetores

void concatena(int v1[], int v2[], int n, int m)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int tamanhoC = n + m;
	int* c = malloc(tamanhoC * sizeof(int));

	while (i < n && j < m)
	{
		if (v1[i] < v2[j])
		{
			c[k] = v1[i];
			k++;      // PS: Eu sei que da pra fazer o incremento "dentro" dos vetores, mas quis deixar o codigo mais visual
			i++;
		}
		else
		{
			c[k] = v2[j];
			k++;
			j++;
		}
	}
	while (i < n)
	{
		c[k] = v1[i];
		k++;
		i++;
	}
	while (j < m)
	{
		c[k] = v2[j];
		k++;
		j++;
	}

	printar(c, tamanhoC);
	free(c);
}
// 8) Escreva uma função que recebe um vetor como parâmetro, a sua função seleciona o primeiro elemento de um vetor
//e rearranja o vetor de forma que todos elementos menores ou iguais ao primeiro elemento fiquem a sua esquerda e
//os maiores a sua direita.
//No vetor{ 5, 6, 2, 7, 9, 1, 8, 3, 7 } após ser rearranjado teríamos{ 1, 3, 2, 5, 9, 7, 8, 6, 7 }. A função deve rearranjar o
//vetor com a complexidade O(n).
void arranjar(int v[], int n)
{
	int j = n - 1;
	int p = 0;
	int i = p + 1;

	while (i <= j)
	{
		if (v[i] <= v[p])
		{
			i++;
		}
		else if (v[j] > v[p])
		{
			j--;
		}
		else
		{
			int aux = v[i];
			v[i] = v[j];
			v[j] = aux;
			i++; i--;
		}
	}
	int aux = v[p];
	v[p] = v[j];
	v[j] = aux;
}
// 9) Escreva um algoritmo que calcula a soma dos prefixos de um vetor em tempo O(n). A soma de prefixos de um vetor V
//em S pode ser definida por :
//S[0] = V[0]
//S[i] = V[i] + V[i – 1] + V[i – 2] + . . . + V[0]
void prefixos(int v[], int tamanho)
{
	int sum = 0;
	int i;
	for (i = 0; i < tamanho; i++)
	{
		sum += v[i];
	}
	printf("%d", sum);
}
//10) Dado um vetor com números pares e ímpares, escreva uma função para colocar todos os números pares à frente no
//vetor e os ímpares ao final.Você não pode usar outro vetor como área auxiliar.A função deve ter deve ter
//complexidade O(n), ou seja, o tamanho do vetor V[].
void parimpar(int v[], int tamanho)
{
	int i = 0;
	int j = tamanho - 1;
	while (i <= j)
	{
		if (v[i] % 2 == 0) i++;
		else if (v[j] % 2 != 0) j--;
		else
		{
			int aux = v[i];
			v[i] = v[j];
			v[j] = aux;
			i++;
			j--;
		}
	}
}
// ex:
// input: 1,2,3,4,5,6
// output: 2,4,6,1,3,5


void main()
{
	// ex 1 
	int v1[] = { 1,2,5,6,7 };
	inverte(v1, 5);
	// ex 2
	int v2[] = { 1,2,4,7 };
	troca(v2, 4);
	// ex 3
	int v3[] = { 4,5,8,1,4,3,5,6,10,12 };
	int st = comprimento(v3, 10);

	//ex 4
	int v4[] = { 5,8,5,3,5,5,15,2,7,9,1,2,4,8,10,14,2,5 };
	int par[2];
	parDeElementos(v4, 18, par);

	//ex 5
	int v5a[5] = { 1,6,7,11,12 };
	int v5b[5] = { 2,6,8,12,20 };
	// Resultado esperado = 6, 12
	inter(v5a, v5b, 6);
	//ex 6
	int v6a[5] = { 1,6,7,11,13 };
	int v6b[5] = { 2,6,8,12,20 };
	diferencaVetores(v6a, v6b, 5);

	// ex7
	int v7a[5] = { 1, 4, 5, 8, 9 }; // 
	int v7b[6] = { 1, 2, 6, 7, 10, 11 };
	concatena(v7a, v7b, 5, 6);

	// ex8
	int v8[9] = { 5, 6, 2, 7, 9, 1, 8, 3, 7 };
	arranjar(v8, 9);
	printar(v8, 9);

	// ex9
	int v9[10] = { 1,2,3,4,5,6,7,8,9,10 };
	prefixos(v9, 10);

	//ex 10
	int v10[6] = { 1,2,3,4,5,6 };
	parimpar(v10, 6);
	printar(v10, 6);
}