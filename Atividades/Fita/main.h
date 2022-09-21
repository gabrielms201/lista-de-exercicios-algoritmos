#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double convertToSeconds(int minutes, int seconds);
FILE* openFile(const char* filepath);
void printArray(double* arr, int size);
void printTime(int value);
bool permute(double* a, int n, double* s, int i, double tapeDuration);
bool validate(double* a, int i);
bool canSave(double* s, int n, double tapeDuration);
void printTapes(double* a, int n, double tapeDuration);
double getMusicsTotalTime(double* musicsTimes, int totalMusics);
#endif