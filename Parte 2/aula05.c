#include <stdio.h>

void printSequence(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		printf("\t%d ", arr[i]);
	printf("\n");
}
void printString(char* arr, int size)
{
	for (int i = 0; i < size; i++)
		printf("\t%c ", arr[i]);
	printf("\n");
}
/// <summary>
/// Print all sequences of a given sequence
/// </summary>
/// <param name="s">: Sequence</param>
/// <param name="i">: Iterator</param>
/// <param name="n">: Sequence size</param>
void generateBinSequence(int* s, int i, int n)
{
	if (i == n) // the sequence is complete
	{
		printSequence(s, n);
		return;
	}
	s[i] = 0;
	generateBinSequence(s, i + 1, n);
	s[i] = 1;
	generateBinSequence(s, i + 1, n);
}
void ex1()
{
	int s[2];
	generateBinSequence(s, 0, 5);
}
/// <summary>
/// Validates if a given sequence is worth to continue generating a sequence of a given array
/// </summary>
/// <param name="a">: Teams array { A, B }</param>
/// <param name="s">: Auxiliar arrya</param>
/// <param name="m">: Score of Team A</param>
/// <param name="n">: Score of Team B</param>
/// <param name="i">: Iterator</param>
/// <returns>bool</returns>
int validate(char* a, char* s, int m, int n, int i)
{
	int greater = (n > m) ? n : m;
	int count = 0;
	for (int j = 0; j < m + n; j++)
	{
		if (a[0] == s[j])
			count++;
	}
	if (count != m && i > greater)
		return 0;
	return 1;
}
/// <summary>
/// Print all scores possible of a given statistics
/// </summary>
/// <param name="a">: Teams array { team A, team B } </param>
/// <param name="s">: Auxiliar arrya </param>
/// <param name="m">: Team A score </param>
/// <param name="n">: Team B score </param>
/// <param name="i">: Iterator </param>
void score(char* a, char* s, int m, int n, int i)
{
	if (i == n + m) // the sequence is complete
	{
		printString(s, n + m);
		return;
	}
	for (int j = 0; j < 2; j++)
	{
		s[i] = a[j];
		if (validate(a, s, m, n, i))
			score(a, s, m, n, i + 1);
	}
}
void ex2()
{
	char a[2] = { 'A', 'B' };
	char buffer[10];
	score(a, buffer, 2, 3, 0);
}

int main()
{
	puts("Exercicio 1: ");
	ex1();
	puts("Exercicio 2: ");
	ex2();
}