#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants and defines
#define MOCKED_ARRAY_SIZE 10
const int CORNER_ON_FIRE = 3;
const int CORNERS = 6;


// ----------------------------------------------------------
// Utils 
void printIntArr(int* arr, int size)
{
	int i;
	printf("{");
	for (i = 0; i < size; i++)
	{
		printf("%d", arr[i]);
		if (i != size - 1)
			printf(", ");
	}
	printf("}");
	printf("\n");
}

void changeAllIntArrayValues(int* arr, int size, int newValue)
{
	int i;
	// Here we can skip the for incrementla instruction to make it run faster:
	// Since we are decrementing 1 from i, when i == 0 (false condition), the loop will break. 
	for (i = size; i--;)
		arr[i] = newValue;
}
// ----------------------------------------------------------

// ----------------------------------------------------------
// Key And Value
typedef struct
{
	int key;
	int value;
} KEY_AND_VALUE;
// ----------------------------------------------------------

// ----------------------------------------------------------
// Path
typedef struct
{
	KEY_AND_VALUE connection;
	int time;
} Path;

Path createPath(int source, int destination, int time)
{
	KEY_AND_VALUE connection = { source, destination };
	Path path = { connection, time };
	return path;
}

void mockPathArray(Path* array)
{
	array[0] = createPath(4, 6, 3);
	array[1] = createPath(5, 2, 4);
	array[2] = createPath(2, 3, 1);
	array[3] = createPath(1, 4, 2);
	array[4] = createPath(3, 5, 1);
	array[5] = createPath(1, 5, 4);
	array[6] = createPath(4, 5, 1);
	array[7] = createPath(5, 6, 1);
	array[8] = createPath(1, 3, 8);
	array[9] = createPath(6, 2, 2);
}
// ----------------------------------------------------------

// ----------------------------------------------------------
// Map
typedef struct
{
	Path* content;
	int* corners;
	int cornerCount;
	unsigned int connectionsCount;
} Map;


Map createMap(Path* content, int totalCorners, int connectionCount)
{
	Map map;
	map.content = content;
	map.cornerCount = totalCorners;
	map.connectionsCount = connectionCount;
	map.corners = (int*)calloc(totalCorners, sizeof(int));
	{
		int i;
		for (i = 0; i < totalCorners; i++)
		{
			map.corners[i] = i + 1;
		}
	}
	return map;
}
void freeMap(Map* map)
{
	free(map->corners);
	free(map->content);
}
void printMap(const Map map)
{
	Path* pathArr = map.content;
	// Creating a scope to isolate i variable
	printf("Total de Esquinas: \n\t");
	{
		int i;
		for (i = 0; i < map.cornerCount; i++)
		{
			printf("%d", map.corners[i]);
			if (i != map.cornerCount - 1)
				printf("-");
		}
		printf("\n");
	}
	// Creating a scope to isolate i variable
	printf("Caminhos do mapa: \n");
	{
		int i;
		for (i = 0; i < 10; i++)
		{
			printf("\t[%d] [%d -> %d : %d min]\n", i, pathArr[i].connection.key, pathArr[i].connection.value, pathArr[i].time);
		}
	}

}
// ----------------------------------------------------------


// ----------------------------------------------------------
// Algorithm
int* fastestRoute(const Map map)
{
	//int* cornersAcessed;
	int* T = (int*)calloc(map.cornerCount, sizeof(int));
	int* E = (int*)calloc(map.connectionsCount, sizeof(int));
	
	// Filling T with max value possible
	changeAllIntArrayValues(T, map.cornerCount, INT_MAX);
	// Inverting E
	changeAllIntArrayValues(E, map.cornerCount, 1);
	printIntArr(E, map.cornerCount);
	



	free(E);
	return T;
}
// ----------------------------------------------------------

// ----------------------------------------------------------
// Driver Code
int main()
{
	Path* arr = (Path*)calloc(MOCKED_ARRAY_SIZE, sizeof(Path));
	mockPathArray(arr);
	// TODO: Criar uma função para criar um array de paths de acordo com o arquivo

	Map map = createMap(arr, CORNERS, MOCKED_ARRAY_SIZE);
	printMap(map);

	int* T = fastestRoute(map);



	// Now we free the allocated memory
	free(T);
	freeMap(&map);
}
// ----------------------------------------------------------