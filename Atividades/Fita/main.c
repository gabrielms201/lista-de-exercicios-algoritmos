#include "main.h"

int main(int argc, char** argv)
{
    // If the path was passed as an argument, take it from argv.
    // If is not, we use the default value ("entrada.txt")
    const char* filePath = argc != 2 ? "entrada.txt" : argv[1];
    //FILE* file = openFile("entrada.txt");
    double tapeDuration = 30;
    int totalMusics = 4;
    
    double* musicsTimes = (double*) calloc(totalMusics, sizeof(double));
    if (musicsTimes == NULL)
    {
        printf("ERRO TENTANDO ALOCAR MEMORIA NA HEAP");
        exit(1);
    }
    double* buffer = (double*) calloc(totalMusics, sizeof(double));
    if (buffer == NULL)
    {
        printf("ERRO TENTANDO ALOCAR MEMORIA NA HEAP");
        exit(1);
    }
    // Hardcoded for a while
    musicsTimes[0] = convertToSeconds(3, 11);
    musicsTimes[1] = convertToSeconds(4, 45);
    musicsTimes[2] = convertToSeconds(6, 8);
    musicsTimes[3] = convertToSeconds(13, 45);

    double totalTime = getMusicsTotalTime(musicsTimes, totalMusics);

    printf("%.2lf Minutos\n", tapeDuration);
    if (totalTime > tapeDuration || !permute(musicsTimes, totalMusics, buffer, 0, tapeDuration))
    {
        printf("Impossivel gravar todas as fitas!\n");
    }

    free(musicsTimes);
    free(buffer);
    return 0;
}

/// <summary>
/// Print all tapes of a given music permutation array
/// </summary>
/// <param name="musicTimesArray">: Array of musics times</param>
/// <param name="n">: Number of elements inside the array</param>
/// <param name="tapeDuration">: Duration of the tape in minutes</param>
void printTapes(double* musicTimesArray, int n, double tapeDuration)
{
    tapeDuration *= 60;
    int time = 0;
    int i;
    printf("Lado A: \n");
    // Printing the side A of the Tape...
    for (i = 0; i < n; i++) 
    {
        // If the current time plus the next music duration is lesser then the side's duration,
        // we need to break the loop and try to add the remaining musics to side B
        if (time + musicTimesArray[i] <= tapeDuration / 2)
        {
            printTime(musicTimesArray[i]);
            printf("\n");
            time += musicTimesArray[i];
        }
        else
            break;
    }
    printf("\nLado B: \n");
    // Printing the side B of the Tape...
    while (i < n)
    {
        printTime(musicTimesArray[i]);
        printf("\n");
        i++;
    }
    printf("\n");
}

/// <summary>
/// Get total time of a array of musics in minutes
/// </summary>
/// <param name="musicsTimes"> array of music times </param>
/// <param name="totalMusics"> number of musics in the array </param>
/// <returns> Total time in minutes </returns>
double getMusicsTotalTime(double* musicsTimes, int totalMusics)
{
    double totalTime = 0;
    int i;
    for (i = 0; i < totalMusics; i++)
    {
        totalTime += musicsTimes[i];
    }
    totalTime /= 60;
    return totalTime;
}
/// <summary>
/// Checks if a permutation can be used to save inside a tape of a given duration
/// </summary>
/// <param name="permutatedSequence">: Given permutation </param>
/// <param name="sequenceSize">: Permutation size</param>
/// <param name="tapeDuration">: Duration of the tape in munutes </param>
/// <returns> True: Can save ; False: Can't save</returns>
bool canSave(double* permutatedSequence, int sequenceSize, double tapeDuration)
{
    tapeDuration *= 60;
    double timeA = 0;
    double timeB = 0;
    int i;
    for (i = 0; i < sequenceSize; i++)
    {
        // If the current time plus the next music duration is lesser then the side's duration,
        // we need to break the loop and try to add the remaining musics to side B
        if (timeA + permutatedSequence[i] <= tapeDuration / 2)
        {
            timeA += permutatedSequence[i];
        }
        else
        {
            break;
        }
    }
    // For the remaining musics (i declared out of scope)
    for (i; i < sequenceSize; i++)
    {
        if (timeB + permutatedSequence[i] <= tapeDuration / 2)
        {
            timeB += permutatedSequence[i];
        }
        else
        {   // If the current time plus the next music duration is lesser then the side's duration,
            // we can't add the music both to the side A and side B, so it's an invalid permutation
            return false;
        }
    }
    // If we can storage all the musics, the given permutation is valid!!
    return true;
}
/// <summary>
/// Given a sequence, tries to get all permutations and check foreach one if all the musics can be saved inside the tape.
/// If the tape can't handle all the musics, returns false
/// otherwise, returns true
/// </summary>
/// <param name="sequence">: Given sequence </param>
/// <param name="n">: Sequence size </param>
/// <param name="auxiliarSequence">: Auxiliar sequence buffer (must have the same time of the sequence)</param>
/// <param name="i">: Iterator (first call should be 0)</param>
/// <param name="tapeDuration">: Total Duration of the tape in minutes </param>
/// <returns> True: The musics can be saved inside the tape ; False: The musics can't be saved inside the tape</returns>
bool permute(double* sequence, int n, double* auxiliarSequence, int i, double tapeDuration)
{
    if (i == n)
    {
        // If we can save the sequence inside the tape, then we print it
        if (canSave(auxiliarSequence, i, tapeDuration))
        {
            printTapes(auxiliarSequence, n, tapeDuration);
            return true;
        }
        // If we don't, we just return false
        return false;
    }
    int j;
    for (j = 0; j < n; j++)
    {
        auxiliarSequence[i] = sequence[j];
        // We only call permute again if the next value that's going to be inserted in the sequence is not repeated
        // (otherwise, it's not a permutation)
        if (validate(auxiliarSequence, i))
        {
            // If we got the right sequence, we can stop
            if (permute(sequence, n, auxiliarSequence, i + 1, tapeDuration))
                return true;
        }
    }
    // We can't storage all the musics
    return false;
}
/// <summary>
/// Checks if the next element that is going to be inserted on the sequence is repeated
/// </summary>
/// <param name="sequence">: Given sequence </param>
/// <param name="i">: iterator </param>
/// <returns> True: Is Valid (not repeated element) ; False: Invalid (repeated element) </returns>
bool validate(double* sequence, int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        // For each element in (0...i), check if it's repeated
        if (sequence[i] == sequence[j])
            return false;
    }
    return true;
}
/// <summary>
/// Print the time of a given value in seconds
/// </summary>
/// <param name="value">: Value in seconds</param>
void printTime(int valueInSeconds)
{
    int hour = (valueInSeconds / 3600.00);
    int min = (valueInSeconds - (3600 * hour))/60;
    int sec = (valueInSeconds - (3600 * hour) - (min * 60));
    printf("%dm%ds ", min, sec);
}
/// <summary>
/// Simple function to print all elements inside an array
/// </summary>
/// <param name="arr">: Given array</param>
/// <param name="size">: Array size</param>
void printArray(double* arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%.2lf ", arr[i]);
    }
    printf("\n");
}
/// <summary>
/// Convert a given time into seconds
/// </summary>
/// <param name="minutes">: Time in minutes</param>
/// <param name="seconds">: Time in seconds</param>
/// <returns>Total time in seconds</returns>
double convertToSeconds(int minutes, int seconds)
{
    return seconds + (minutes * 60.00);
}


// descrever
FILE* openFile(const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (!file)
    {
        printf("ERRO TENTANDO ABRIR O ARQUIVO!! \n");
        exit(1);
    }
    return file;
}



