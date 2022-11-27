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
/// <summary>
/// Quick function to change all values of an array
/// </summary>
/// <param name="arr"></param>
/// <param name="size"></param>
/// <param name="newValue"></param>
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

/// <summary>
/// Creates a path based on given parameters
/// </summary>
/// <param name="source"></param>
/// <param name="destination"></param>
/// <param name="time"></param>
/// <returns></returns>
Path createPath(int source, int destination, int time)
{
	KEY_AND_VALUE connection = { source, destination };
	Path path = { connection, time };
	return path;
}

/// <summary>
/// Creates an array of paths (used on tests without files)
/// </summary>
/// <param name="array"></param>
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
	for (; *i < totalPaths; (*i)++)
	{
		if (connections[*i].connection.key != corner)
		{
			break;
		}
		count++;
	}
	return count;
}
/// <summary>
/// Storages each destination based on it's key and value (corner and time)
/// </summary>
/// <param name="connections"></param>
/// <param name="i"></param>
/// <param name="j"></param>
/// <param name="destinations"></param>
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
// Ex:
// Corner 1 can acess corner 4 and 6
typedef struct
{
	int source;
	KEY_AND_VALUE* destinations; // key: corner - value: time
	int totalPaths;
} CornerWay;

/// <summary>
/// Creates an array of ways
/// </summary>
/// <param name="connections"></param>
/// <param name="totalConnections"></param>
/// <param name="cornerCount"></param>
/// <returns>Array of ways</returns>
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
			printf("Nao ha caminhos para a esquina %d!", i + 1);
			exit(1);
		}
		destinations = (KEY_AND_VALUE*)calloc(pathCountForThisCorner, sizeof(KEY_AND_VALUE));
		storageDestinations(connections, lastCornerIndexCountedBefore, lastCornerIndexCounted, destinations);
		CornerWay way = { i + 1, destinations, pathCountForThisCorner };
		ways[i] = way;
	}
	return ways;
}

/// <summary>
/// Prints all the values of a way
/// </summary>
/// <param name="way"></param>
void printWay(const CornerWay way)
{
	printf("Esquina (%d): ", way.source);
	int i;
	for (i = 0; i < way.totalPaths; i++)
	{
		printf("%d (%d min) ", way.destinations[i].key, way.destinations[i].value);
	}
	printf("\n");
	return;
}

/// <summary>
/// Free array of ways
/// </summary>
/// <param name="way"></param>
void freeWay(CornerWay* way)
{
	free(way->destinations);
}
// ----------------------------------------------------------
// ResultAndTime
typedef struct
{
	int* T;
	int* R;
	int size;
} ResultAndTime;

/// <summary>
/// Free all array results
/// </summary>
/// <param name="result"></param>
void freeResult(ResultAndTime* result)
{
	free(result->T);
	free(result->R);
}

/// <summary>
/// Recursively prints the best route based on R
/// </summary>
/// <param name="result"></param>
/// <param name="corner"></param>
/// <param name="first"></param>
void printRoute(ResultAndTime const* const result, int corner, int first)
{
	corner = corner - 1;
	if (result->R[corner] == 0)
	{
		return;
	}
	printRoute(result, result->R[corner], 0);
	printf("%d - ", result->R[corner]);
	if (first)
		printf("%d\n", corner + 1);
}

/// <summary>
/// Returns the value of T on corner index-1
/// </summary>
/// <param name="result"></param>
/// <param name="corner"></param>
/// <returns></returns>
int getCornerTime(ResultAndTime const* const result, int corner)
{
	return result->T[corner - 1];
}

/// <summary>
/// Prints the route to a corner, and the time to reach it
/// </summary>
/// <param name="result"></param>
/// <param name="targetCorner"></param>
void printResult(ResultAndTime const* const result, int targetCorner)
{
	printf("Rota para a esquina %d:\n", targetCorner);
	printRoute(result, targetCorner, 1);
	int time = getCornerTime(result, targetCorner);
	printf("Tempo para chegar na esquina %d: %d", targetCorner, time);
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
			Path nextPath = paths[j + 1];
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
	{
		int i;
		for (i = 0; i < map.cornerCount; i++)
		{
			printWay(map.ways[i]);
		}
	}


}
// ----------------------------------------------------------


// ----------------------------------------------------------
// Algorithm

/// <summary>
/// Find the lower cost corner in T (v)
/// "v eh uma esquina em E com o menor custo no vetor T[]"
/// </summary>
/// <param name="T"></param>
/// <param name="i"></param>
/// <param name="size"></param>
/// <param name="E"></param>
/// <returns></returns>
int findLowestCostCorner(const int* const T, int i, int size, const int* E)
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
	for (; i < size; i++)
	{
		if (T[i] < T[lowerIndex] && E[i] != 0)
			lowerIndex = i;
	}
	return lowerIndex;
}
/// <summary>
/// Main Algo
/// Here we find the best route and time for each corner inside a given map
/// </summary>
/// <param name="map"></param>
/// <returns></returns>
ResultAndTime fastestRoute(const Map* const map)
{
	// T array: best time for all corners
	int* T = (int*)calloc(map->cornerCount, sizeof(int));
	// E representes all corners
	// If the value is present, 1
	// If the value is not present, 0.
	int* E = (int*)calloc(map->cornerCount, sizeof(int));
	int* R = (int*)calloc(map->cornerCount, sizeof(int));
	ResultAndTime result = { T, R, map->cornerCount };

	// Filling T with max value possible
	changeAllIntArrayValues(T, map->cornerCount, INT_MAX);
	// 1 - 1 = 0min
	T[0] = 0;
	// Inverting E to 1
	changeAllIntArrayValues(E, map->cornerCount, 1);

	// Instead of doing a search everytime, we can just assign a variable with the original size of E, and then
	// we decrease it's value everytime we "remove" an element
	int availableCornersCount = map->cornerCount;

	while (availableCornersCount != 0)
	{
		int i;
		int lowerIndex = findLowestCostCorner(T, 0, map->cornerCount, E); // Corner in E[] with the lowest value in T[] 
		//int V = E[lowerIndex];

		// "removing" corner v from E:
		E[lowerIndex] = 0;
		availableCornersCount--;
		CornerWay accessiblePaths = map->ways[lowerIndex];
		// For each acessible path from your point (lowerIndex)
		for (i = 0; i < accessiblePaths.totalPaths; i++)
		{
			// Corner Key and Value.
			// Key: Corner number
			// Value: Corner time 
			KEY_AND_VALUE cornerKeyAndValue = accessiblePaths.destinations[i];
			// if the corner is not present in E, we go to the next one.
			int accessibleCorner = cornerKeyAndValue.key; // "e" variable
			int accessibleCornerTime = cornerKeyAndValue.value;
			// If the corner is not in E, we break the loop and goto the next one!
			if (E[accessibleCorner - 1] == 0)
			{
				break;
			}
			if (T[accessibleCorner - 1] > T[lowerIndex] + accessibleCornerTime)
			{
				// Storaging the time to reach this corner
				T[accessibleCorner - 1] = T[lowerIndex] + accessibleCornerTime;
				// Storaging the corner to reach this corner
				R[accessibleCorner - 1] = accessiblePaths.source;
			}
		}
	}
	free(E);
	return result;
}
// ----------------------------------------------------------
void run(const char* filepath)
{
	FILE* file = fopen(filepath, "r");
	if (!file)
	{
		printf("ERRO TENTANDO ABRIR O ARQUIVO!! \n");
		exit(1);
	}
	//
	int targetCorner = 0;
	int arraySize = 0;
	int cornerQty = 0;

	// TODO: Criar uma função para criar um array de paths de acordo com o arquivo
	Path* arr = (Path*)calloc(arraySize, sizeof(Path));
	// Leitura da esquina destino
	fscanf(file, "%d", &targetCorner);
	// Leitura da quantidade de esquinas
	fscanf(file, "%d", &cornerQty);

	int source = 1;
	int destiny = 1;
	int time = 1;
	int index = 0;
	while (source != 0)
	{
		fscanf(file, "%d", &source);
		if (source == 0)
		{
			break;
		}
		arraySize++;
		arr = (Path*)realloc(arr, arraySize * sizeof(Path));
		fscanf(file, "%d", &destiny);
		fscanf(file, "%d", &time);
		arr[index] = createPath(source, destiny, time);
		int test = 32;
		index++;
	}

	Map map = createMap(arr, cornerQty, arraySize);
	printMap(map);

	ResultAndTime result = fastestRoute(&map);

	// Vector result
	printf("Vetor T:\n");
	printIntArr(result.T, result.size);
	printf("Vetor R:\n");
	printIntArr(result.R, result.size);


	printResult(&result, targetCorner);

	// Now we free the allocated memory
	freeResult(&result);
	freeMap(&map);


	fclose(file);
}
// ----------------------------------------------------------
// Driver Code
int main(int argc, char** argv)
{
	const char* filePath;
	if (argc == 2)
	{
		filePath = argv[1];
	}
	else
	{
		filePath = "bombeiros.txt";
	}
	run(filePath);
}
// ----------------------------------------------------------