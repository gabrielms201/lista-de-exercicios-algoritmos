#include <stdio.h>

// Check if the sequence lexicographic is smaller
// r: First Sequence
// s: Second Sequence
// j: First Sequence size
// k: Second Sequence size
int isSmaller(int* r, int j, int* s, int k)
{
	for (int i = 0; i < j && i < k; i++)
	{
		if (r[i] < s[i]) return 1;
		if (r[i] > s[i]) return 0;
	}

	// Here s[1...j] and s[1...j] are equal
	// now we need to know if j<k
	if (j < k) return 1;
	return 0;
}
void ex1()
{
	int r[5] = { 4,1,2,5,6 };
	int s[6] = { 4,1,2,5,6,9 };

	int rIsSmaller = isSmaller(r, 5, s, 6);
	if (rIsSmaller) 
		printf("r eh menor lexicograficamente que s!\n");
	else 
		printf("r NAO eh menor lexicograficamente que s!\n");
}
// Check if the sequence lexicographic is smaller, greater or equal
// r: First Sequence
// s: Second Sequence
// j: First Sequence size
// k: Second Sequence size
// Returns: 1 - Smaller, 0 - Equal, -1 - Greater
int checkSequenceOrder(int* r, int j, int* s, int k)
{
	for (int i = 0; i < j && i < k; i++)
	{
		if (r[i] < s[i]) return 1;
		if (r[i] > s[i]) return -1;
	}

	// Here s[1...j] and s[1...j] are equal
	// now we need to know if j<k
	if (j < k) return 1;
	if (j == k) return 0;
	// j > k
	return -1;
}
const char* orderToString(int result)
{
	switch (result)
	{
	case 1:
		return "is smaller then";
	case 0:
		return "is equal to";
	case -1:
		return "is greater then";
	default:
		break;
	}
}
void ex2()
{
	// test 1 - should be greater
	{
		int r[4] = { 4,1,3,2 };
		int s[6] = { 4,1,2,5,6 };
		int result = checkSequenceOrder(r, 4, s, 6);
		printf("r %s s\n", orderToString(result));
	}
	// test 2 - should be smaller
	{
		int r[5] = { 4,1,2,5,6 };
		int s[6] = { 4,1,2,5,6,9 };
		int result = checkSequenceOrder(r, 5, s, 6);
		printf("r %s s\n", orderToString(result));
	}
	// test 2 - should be equal
	{
		int r[4] = { 4,1,3,2 };
		int s[4] = { 4,1,3,2 };
		int result = checkSequenceOrder(r, 4, s, 4);
		printf("r %s s\n", orderToString(result));
	}
	
}
// Checks if once sequence is a subsequence of another
// s: First Sequence
// k: First Sequence Size
// a: Second Sequence
// n: Second Sequence Size
// Returns: bool
int isSubsequence(int* s, int k, int* a, int n)
{
	int flags = 0;
	for (int i = 0; i < n; i ++)
	{
		for (int j = 0; j < k; j++)
		{
			if (s[j] == a[i])
			{
				flags++;
				continue;
			}
		}
	}
	if (flags == k) return 1;
	return 0;
}
void ex3()
{
	int s[4] = { 2,3,4,5 };
	int n[8] = { 1,2,3,4,5,6,7,8 };
	int result = isSubsequence(s, 4, n, 8);
	if (result)
		puts("s is a subsequence of n");
	else
		puts("s is NOT a subsequence of n");
}

//
// 
// 
// 
//
void ex5()
{

}
// Counts Consecutive numbers sequences of a given sequence
// s: Sequence
// n: Sequence size
// returns: consecutive  numbers count
int countConsecutiveSequences(int* s, int n)
{
	// O(n)
	int count = 1;
	for (int i = 0; i < n - 1; i++)
		if (s[i] != s[i + 1]) count++;
	return count;
}
void ex5()
{
	// example 1
	{
		int s[11] = { 5, 2, 2, 3, 4, 4, 4, 4, 4, 1, 1 };
		int result = countConsecutiveSequences(s, 11);
		printf("Exemplo 1: Sequencias consecutivas: %d\n", result);
	}
	// example 2
	{
		int s[10] = { 3, 3, -1, -1, -1, 12, 12, 12, 3, 3 };
		int result = countConsecutiveSequences(s, 10);
		printf("Exemplo 2: Sequencias consecutivas: %d\n", result);
	}
}


int main()
{
	puts("Exercicio 1: ");
	ex1();
	puts("Exercicio 2: ");
	ex2();
	puts("Exercicio 3: ");
	ex3();
	puts("Exercicio 4: ");
	ex4();
	puts("Exercicio 5: ");
	ex5();
}