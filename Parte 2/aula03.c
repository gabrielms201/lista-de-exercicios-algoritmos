#include <stdio.h>
#include <memory.h>
#include <malloc.h>

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
		printf("\tr eh menor lexicograficamente que s!\n");
	else 
		printf("\tr NAO eh menor lexicograficamente que s!\n");
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
		printf("\tr %s s\n", orderToString(result));
	}
	// test 2 - should be smaller
	{
		int r[5] = { 4,1,2,5,6 };
		int s[6] = { 4,1,2,5,6,9 };
		int result = checkSequenceOrder(r, 5, s, 6);
		printf("\tr %s s\n", orderToString(result));
	}
	// test 2 - should be equal
	{
		int r[4] = { 4,1,3,2 };
		int s[4] = { 4,1,3,2 };
		int result = checkSequenceOrder(r, 4, s, 4);
		printf("\tr %s s\n", orderToString(result));
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
		puts("\ts is a subsequence of n");
	else
		puts("\ts is NOT a subsequence of n");
}

// Checks if a sequence is a segment (contiguous sequence)
// s: sequence to check
// j: first sequence size
// a: second sequence
// n: second sequence size
// Returns: bool
int isSegment(int* s, int j, int* a, int n)
{
	int i = 0;
	int k = 0;
	int count = 0;
	while (k < n)
	{
		if (a[k] != s[i])
			k++;
		else
		{
			if (count == 0) count++;
			if (i == j-1) break;
			if (s[i + 1] == s[i] + 1)
				count++;
			k++;
			i++; 
		}
	}
	if (count == j) 
		return 1;
	else 
		return 0;
}
void ex4()
{
	// example: A = [1,2,3,4]
	// S could be : [[1], [1, 2], [1, 2, 3], [1, 2, 3, 4], [2], [2, 3], [2, 3, 4], [3], [3, 4], [4]]
	int s[] = { 1,2,3 };
	int a[4] = { 1,2,3,4 };
	int result = isSegment(s, 3, a, 4);
	if (result)
		printf("\ts is a segment of a!\n");
	else
		printf("\tf is not a segment of a!\n");

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
		printf("\tExemplo 1: Sequencias consecutivas: %d\n", result);
	}
	// example 2
	{
		int s[10] = { 3, 3, -1, -1, -1, 12, 12, 12, 3, 3 };
		int result = countConsecutiveSequences(s, 10);
		printf("\tExemplo 2: Sequencias consecutivas: %d\n", result);
	}
}
// Count the max length of a growing continguos subsequence
// s: sequence
// n: sequence size
// Returns: max length counting
int maxGrowingSegmentLength(int* s, int n)
{
	int streak = 0;
	int maxStreak = 0;
	for (int i = 0; i < n-1; i++)
	{
		if (s[i + 1] > s[i])
			streak ++;
		else
			streak = 1;
		if (streak > maxStreak)
			maxStreak = streak;
	}
	return maxStreak;
}
void ex6()
{
	// Example: 
	// s = 5 10 3 2 4 7 9 8 5
	// maxGrowingSegment(s) = 4  | (2,4,7,9)
	// test 1
	{
		int s[9] = { 5,10,3,2,4,7,9,8,5 };
		int value = maxGrowingSegmentLength(s, 9);
		printf("\t test 1: max growing = %d\n", value); // should be 4
	}
	// test 2
	{
		int s[5] = { 10,8,7,5,2 };
		int value = maxGrowingSegmentLength(s, 5);
		printf("\t test 2: max growing = %d\n", value); // should be 1
	}
}

// Get the i and m of two consecutive contiguous sequences inside a sequence
// s: sequence
// size: sequence size
// output: (out) i and m (pass an array to get it)
void func(int* s, int size, int output[2])
{
	int i = 0;
	int m = 0;
	int firstFound = 0;
	for (int j = 0; j <size-1; j ++)
	{
		for (int k = j+1; k < size-1; k++)
		{
			if (s[j] == s[k] && !firstFound)
			{
				i = j + 1;
				m = k - j;
				firstFound = 1;
			}
		}
	}
	output[0] = i;
	output[1] = m;
}

void ex7()
{
	int output[2] = { 0,0 };
	int s[8] = { 7, 9, 5, 4, 5, 4, 8, 6 };
	func(s, 8, output);
	printf("i = %d | m = %d", output[0], output[1]);
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
	puts("Exercicio 6: ");
	ex6();
	puts("Exercicio : ");
	ex7();
}