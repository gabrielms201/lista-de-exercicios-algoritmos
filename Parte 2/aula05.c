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
// i: index
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
	generateBinSequence(s, 0, 2);
}
int main()
{
	ex1();
}