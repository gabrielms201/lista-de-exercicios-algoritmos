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

/// <summary>
/// Returns number os paths of a corner
/// </summary>
/// <param name="paths"></param>
/// <returns></returns>
int countCornerPaths(Path* const connections, int* i, int corner, int totalPaths)
{
	int count = 0;
	for (;*i < totalPaths; (*i)++)
	{
		if (connections[*i].connection.key != corner)
		{
			break;
		}
		count++;
	}
	return count;
}

void storageDestinations(Path* const connections, int i, int j, KEY_AND_VALUE* destinations)
{
	int index = 0;
	while (i < j)
	{
		destinations[index].key = (connections[i].connection.value);
		destinations[index].value = (connections[i].time);

		index++;
		i++;
	}
}
// ----------------------------------------------------------

// ----------------------------------------------------------
// CornerWays
typedef struct 
{
	int source;
	KEY_AND_VALUE* destinations; // destiny[1][X]
	int totalPaths;
} CornerWay;

CornerWay* createWays(Path* connections, int totalConnections, int cornerCount)
{
	CornerWay* ways = (CornerWay*)calloc(cornerCount, sizeof(CornerWay));

	int lastCornerIndexCounted = 0;
	int lastCornerIndexCountedBefore = 0;
	KEY_AND_VALUE* destinations = NULL;
	int i, j;
	int pathCountForThisCorner = 1;
	for (i = 0; i < cornerCount; i++)
	{
		lastCornerIndexCountedBefore = lastCornerIndexCounted;
		pathCountForThisCorner = countCornerPaths(connections, &lastCornerIndexCounted, i + 1, totalConnections);
		if (pathCountForThisCorner == 0)
		{
			printf("Nao ha caminhos para a esquina %d!", i+1);
			exit(1);
		}
		destinations = (KEY_AND_VALUE*)calloc(pathCountForThisCorner, sizeof(KEY_AND_VALUE));
		storageDestinations(connections, lastCornerIndexCountedBefore, lastCornerIndexCounted, destinations);
		CornerWay way = { i + 1, destinations, pathCountForThisCorner };
		ways[i] = way;
	}
	for (j = 0; j < totalConnections; j++)
	{

	}
	return ways;
}
void printWay(const CornerWay way)
{
	printf("Esquina (%d): ", way.source);
	int i;
	for ( i = 0; i < way.totalPaths; i++)
	{
		printf("%d (%d min) ", way.destinations[i].key, way.destinations[i].value);
	}
	printf("\n");
	return;
}
void freeWay(CornerWay* way)
{
	free(way->destinations);
}



// ----------------------------------------------------------

// ----------------------------------------------------------
// Map
typedef struct
{
	Path* connections;
	int* corners;
	int cornerCount;
	unsigned int connectionsCount;
	CornerWay* ways;
} Map;

/// <summary>
/// Sort all paths by corner number.
/// It'well help us to track all connections for a corner more efficiently
/// </summary>
/// <param name="paths"></param>
/// <param name="connectionsCount"></param>
void sortPathsByCorner(Path* const paths, int connectionsCount)
{
	int i, j;
	for (i = 0; i < connectionsCount; i++)
	{
		for (j = 0; j < connectionsCount - 1; j++)
		{
			Path currentPath = paths[j];
			Path nextPath = paths[j+1];
			if (currentPath.connection.key > nextPath.connection.key)
			{
				Path temp = paths[j];
				paths[j] = paths[j + 1];
				paths[j + 1] = temp;
			}
		}
	}
}
/// <summary>
/// Creates a map to track all connections
/// </summary>
/// <param name="connections"></param>
/// <param name="totalCorners"></param>
/// <param name="connectionsCount"></param>
/// <returns></returns>
Map createMap(Path* const connections, int totalCorners, int connectionsCount)
{
	Map map;
	sortPathsByCorner(connections, connectionsCount);
	map.connections = connections;
	map.cornerCount = totalCorners;
	map.connectionsCount = connectionsCount;
	map.corners = (int*)calloc(totalCorners, sizeof(int));
	{
		int i;
		for (i = 0; i < totalCorners; i++)
		{
			map.corners[i] = i + 1;
		}
	}
	map.ways = createWays(connections, connectionsCount, totalCorners);

	
	return map;
}

/// <summary>
/// Free Heap Allocated Memory of a Map instance
/// </summary>
/// <param name="map"></param>
void freeMap(Map* map)
{
	int i;
	for (i = 0; i < map->cornerCount; i++)
	{
		freeWay(&(map->ways[i]));
	}
	free(map->corners);
	free(map->connections);
	free(map->ways);
}
/// <summary>
/// Print all Map informations
/// </summary>
/// <param name="map"></param>
void printMap(const Map map)
{
	Path* pathArr = map.connections;
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
	// Creating a scope to isolate i variable
	printf("Ways: MUDAR POR FAVOR\n");
	{
		int i;
		for (i = 0; i <map.cornerCount; i++)
		{
			printWay(map.ways[i]);
		}
	}


}
// ----------------------------------------------------------


// ----------------------------------------------------------
// Algorithm

int findLowerCostCorner(const int* const T, int i, int size, const int* E)
{
	int lowerIndex = 0;
	int j;
	for (j = 0; j < size; j++)
	{
		if (E[j] == 1)
		{
			lowerIndex = j;
			break;
		}
	}
	for (;i < size; i++)
	{
		if (T[i] < T[lowerIndex] && E[i] != 0)
			lowerIndex = i;
	}
	return lowerIndex;
}

int* fastestRoute(const Map* const map)
{
	int* T = (int*)calloc(map->cornerCount, sizeof(int));
	// E representes all corners
	// If the value is present, 1
	// If the value is not present, 0.
	int* E = (int*)calloc(map->cornerCount, sizeof(int));
	
	// Filling T with max value possible
	changeAllIntArrayValues(T, map->cornerCount, INT_MAX);
	// 1 - 1 = 0min
	T[0] = 0;
	// Inverting E to 1
	changeAllIntArrayValues(E, map->cornerCount, 1);
	int availableCornersCount = map->cornerCount;
	int index = 0;

	printIntArr(T, map->cornerCount);
	while (availableCornersCount != 0)
	{
		// Vamos depois arrumar isso. Uma ideia: Ordenar o vetor.
		int i;
		int lowerIndex = findLowerCostCorner(T, 0, map->cornerCount, E); // v
		int V = E[lowerIndex];
		E[lowerIndex] = 0; // removing corner v from E
		availableCornersCount--;
		CornerWay acessablePaths = map->ways[lowerIndex];
		for (i = 0; i < acessablePaths.totalPaths; i++)
		{
			KEY_AND_VALUE e = acessablePaths.destinations[i];
			// if the corner is not present in E, we go to the next one.
			if (E[e.key - 1] == 0)
				break;
			if (T[e.key-1] > T[lowerIndex] + e.value)
			{
				T[e.key-1] = T[lowerIndex] + e.value;
			}
		}
		printIntArr(E, map->cornerCount);
		index++;
		
	}

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

	int* T = fastestRoute(&map);


	// Now we free the allocated memory
	free(T);
	freeMap(&map);
}
// ----------------------------------------------------------