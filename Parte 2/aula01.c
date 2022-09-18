#include <stdio.h>

// Ex 1
// Recursive Power
int power(int a, int n)
{
	if (n == 0)
	{
		return 1;
	}

	return power(a, n - 1) * a;
}
int ex1()
{
	unsigned int a = power(30, 5);
	printf("30 ^ 5 : %d\n", a);
}

// Ex 2
// Recursive Factorial
unsigned long long factorial(int n)
{
	// I know we can easily get overflow even using long long, but the exercise is not asking to deal with overflow, 
	// so we should go on the easiest way
	if (n == 0)
	{
		return 1;
	}
	return n * factorial(n - 1);
}
void ex2()
{
	int n = 15;
	unsigned long long fact = factorial(n);
	printf("%d! = %llu", n, fact);
}
// Ex 3
// Recursive Fibonnaci 
int fibonacci(int n)
{
	if (n == 0 || n == 1)
	{
		return n;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}
void ex3()
{
	int order = 10;
	int result = fibonacci(order);
	printf("F(%d) = %d", order, result);
}

// Ex4
// Recursive Positive int Array Operations: Search, minValue, sumAllElements, mean
int search(int value, int* arr, int size, int index)
{
	if (index == size - 1)
	{
		return -1;
	}
	if (arr[index] == value)
	{
		return index;
	}
	return search(value, arr, size, index + 1);
}
int minValue(int* arr, int size)
{
	if (size == 0)
	{
		return arr[0];
	}
	if (arr[size] < minValue(arr, size - 1))
	{
		return arr[size];
	}
	else
	{
		return minValue(arr, size - 1);
	}
}
int sumAllElements(int* arr, int size)
{
	if (size <= 0)
	{
		return 0;
	}
	return(arr[size - 1] + sumAllElements(arr, size - 1));
}
double mean(int* arr, int size)
{
	if (size == 0)
	{
		return (float)arr[size];
	}
	if (size < 0)
	{
		return 0;
	}
	//AVG = SUM(1...N) / N ----> SUM(1...N) = AVG * N
	// avg of (1...N-1)
	float sum = mean(arr, size - 1) * (size - 1); 
	// We are getting AVG of N-1 to go down till we break the stop point
	return ((sum + arr[size - 1]) / size);
}

void ex4()
{
	int arr[5] = { 4,9,10,2,1 };
	// a-)
	{
		int searchingValue = 4;
		int searchResult = search(searchingValue, arr, 5, 0);

		if (searchResult == -1)
			printf("\ta: Value not found!\n");
		else
			printf("\ta: Searching result for value = %d: array[%d]\n", searchingValue, searchResult);
	}
	// b-)
	{
		int min = minValue(arr, 5);
		printf("\tb: Min value for the array: %d\n", min);
	}
	// c-)
	{
		int sum = sumAllElements(arr, 5); // should be 26
		printf("\tc: Sum of all elements of the array: %d\n", sum);
	}
	// d-)
	{
		double average = mean(arr, 5); // should be 5.2
		printf("\td:Mean of the array: %lf\n", average);
	}
}
// Ex 5
// Returns the product of two numbers
// a: value 1
// b: value 2
int mult(int a, int b)
{
	if (b == 1)
	{
		return a;
	}
	if (b > 1)
	{
		return mult(a, b - 1) + a;
	}
	return mult(a, b - 1);
}
void ex5()
{
	int value = mult(3, 4);
	printf("%d\n", value);
}

int main()
{
	printf("Exercicio 1: \n");
	ex1();
	printf("Exercicio 2: \n");
	ex2();
	printf("Exercicio 3: \n");
	ex3();
	printf("Exercicio 4: \n");
	ex4();
	printf("Exercicio 5: \n");
	ex5();
}