#include <stdio.h>

void printSequence(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		printf("\t%d ", arr[i]);
	printf("\n");
}


// Print all sequences of a given sequence
// a: Sequence
// n: Sequence size
// s: Auxiliar array (same size of the sequence)
// i: Auxiliar array working index (first call should be 0)
void generateSequence(int* a, int n, int* s, int i)
{
	if (i == n) // the sequence is complete
	{
		printSequence(s, n);
		return;
	}

	for (int j = 0; j < n; j++)
	{
		s[i] = a[j];
		generateSequence(a, n, s, i + 1);
	}
}
void ex1()
{
	int a[3] = { 1,2,3 };
	int s[3];
	generateSequence(a, 3, s, 0);
}

 // Print all sequences of a given sequence
 // a: Sequence
 // n: Sequence size
 // s: Auxiliar array (same size of the sequence)
 // i: Auxiliar array working index (first call should be 0)
 // t: Auxiliar array size
void newGenerateSequence(int* a, int n, int* s, int i, int t)
{
	if (i == t) // the sequence is complete
	{
		printSequence(s, t);
		return;
	}

	for (int j = 0; j < n; j++)
	{
		s[i] = a[j];
		newGenerateSequence(a, n, s, i + 1, t);
	}
}
void ex2()
{
	int a[4] = { 1,2,3, 4 };
	int s[3] = { 0,0,0 };
	newGenerateSequence(a, 4, s, 0, 3);
}

// Print subsequences of a sequence
// a: Sequence
// n: Sequence size
// s: Auxiliar sequence
// i,j: indexes
void generateSubSequence(int* a, int n, int* s, int i, int j)
{
	while (j < n)
	{
		s[i] = a[j];
		printSequence(s, i+1); // i+1: size to print. Since 0 is the first index.
		generateSubSequence(a, n, s, i + 1, j + 1);
		j++;
	}
}
void ex3()
{
	int a[3] = { 1,2,3 };
	int s[3] = { 0,0,0 };
	generateSubSequence(a,3,s,0,0);
}

// Verify if s[i] is diferent then the others elements
// return: 0 isn't different, 1: is differente
int verify(int* s, int i)
{
	for (int j = 0; j < i; j++)
	{
		if (s[i] == s[j])
			return 0;
	}
	return 1;
}

// Prints all permutations of a given sequence
// a: Sequence
// n: Sequence size
// s: Auxiliar array (same size of the sequence)
// i: Auxiliar array working index (first call should be 0)
void permute(int* a, int n, int* s, int i)
{
	if (i == n)
	{
		printSequence(s, n);
		return;
	}
	for (int j = 0; j < n; j++)
	{
		s[i] = a[j];
		if (verify(s, i))
			permute(a, n, s, i + 1);
	}
}
void ex4()
{
	int a[3] = { 1,2,3 };
	int s[3] = { 0,0,0 };
	permute(a, 3, s, 0, 0);
}

int main()
{
	puts("Exercicio 1");
	ex1();
	puts("Exercicio 2");
	ex2();
	puts("Exercicio 3");
	ex3();
	puts("Exercicio 4");
	ex4();
}