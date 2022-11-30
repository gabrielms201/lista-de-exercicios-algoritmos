#include <stdio.h>
typedef struct
{
	int s, f;
}Atividade;


void bubble(Atividade A[], int N)
{
	for (int k = 0; k < N; k++)
	{
		for (int i = 0; i < N - 1; i++)
		{
			if (A[i].f > A[i + 1].f)
			{
				Atividade temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
			}
		}
	}
}
void printArr(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d - ", arr[i]);
	}
	printf("\n");
}
void printAtvArr(Atividade* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("f:%d -s:%d ", arr[i].f, arr[i].s);
	}
	printf("\n");
}
void printCedulas(int* arr, int n)
{
	int C[] = { 100, 50, 20, 10, 5, 2 };
	for (int i = 0; i < n; i++)
	{
		printf("%d notas de %d\n", arr[i], C[i]);
	}
}
void printMoedas(int* arr, int n)
{
	double M[] = { 1, 0.5, 0.25, 0.1, 0.05, 0.01 };
	for (int i = 0; i < n; i++)
	{
		printf("%d moedas de %lf\n", arr[i], M[i]);
	}
}

// O algoritmo recebe um conjunto C = { 100,50,25,10,1 } com os valores das
// moedas já em ordem decrescente e um determinado valor do troco que se
// deseja calcular.A saída do algoritmo é a sequência S de moedas usadas para
// determinar o troco.
void moedas(int valor)
{
	int C[] = { 100,50,25,10,1 };
	int S[] = { 0,0,0,0,0 };
	int n = 5;
	int i = 0;
	while (valor > 0 && i < n)
	{
		if (valor - C[i] >= 0)
		{
			valor -= C[i];
			S[i] += 1;
		}
		else
		{
			i++;
		}
	}
	printArr(S, n);
}


/// Atividades
Atividade* atvd(Atividade* A, int N, int* qde)
{
	Atividade* S = (Atividade*)malloc(N * sizeof(Atividade));
	bubble(A, N);
	*qde = 1;
	S[0] = A[0];
	int i = 0;
	for (int j = 1; j < N; j++)
	{
		// Se a atividade atual tiver um inicio maior que a ultima atvd adicionada:
		if (A[j].s >= A[i].f)
		{
			S[(*qde)] = A[j];
			(*qde)++;
			i = j;
		}
	}
	return S;
}
void atvdRec(Atividade* A, int N, int* qde, Atividade* S, int j, int i)
{
	if (j >= N)
	{
		return;
	}
	if (A[j].s >= A[i].f)
	{
		S[(*qde)] = A[j];
		(*qde)++;
		i = j;
	}
	atvdRec(A, N, qde, S, j + 1, i);
}
// Notas e moedas
//Leia um valor de ponto flutuante com duas casas decimais.Este valor representa
//um valor monetário.A seguir, calcule o menor número de notas e moedas
//possíveis no qual o valor pode ser decomposto.As notas consideradas são de
//100, 50, 20, 10, 5, 2. As moedas possíveis são de 1, 0.50, 0.25, 0.10,
//0.05 e 0.01.O seu programa deve a relação de notas necessárias,

int dinheiro(double valor)
{
	int qdeCedulas = 6;
	int qdeMoedas = 6;
	int C[] = { 100, 50, 20, 10, 5, 2 };
	double M[] = { 1, 0.5, 0.25, 0.1, 0.05, 0.01};
	int SC[] = { 0, 0, 0, 0 ,0, 0 };
	int SM[] = { 0,0,0,0,0,0 };
	int i = 0;
	// Cedulas
	while (valor >= 0 && i < qdeCedulas)
	{
		if (valor - C[i] >= 0)
		{
			SC[i] += 1;
			valor -= C[i];
		}
		else
		{
			i++;
		}
	}
	// Moedas
	i = 0;
	while (valor >= 0 && i < qdeMoedas)
	{
		if (valor - M[i] >= 0)
		{
			SM[i] += 1;
			valor -= M[i];
		}
		else
		{
			i++;
		}
	}
	printCedulas(SC, qdeCedulas);
	printMoedas(SM, qdeMoedas);

}
int ex3()
{
	double valor = 576.73;
	dinheiro(valor);
}


int main()
{
	puts("Exercicio 1:");
	moedas(1937);

	//
	puts("Exercicio 2:");
	Atividade A[] = { {3,5},{0,6},{5,9},{2,13},{6,10},{3,8},{1,4},{5,7},{12,14}, {8,12},{8,11} };
	int qtde = 0;
	Atividade* s = (Atividade*)malloc(11 * sizeof(Atividade));
	bubble(A, 11);
	qtde = 1;
	s[0] = A[0];
	atvdRec(A, 11, &qtde, s, 1, 0);
	printAtvArr(s, qtde);
	free(s);
	//
	puts("Exercicio 3:");
	ex3();

}