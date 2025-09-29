#ifndef BASICFUNCTIONS_H_INCLUDED
#define BASICFUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

int PrintFunctions(int type, int sleepTime, char charToPrint[]);

int LoadingAnimation(int sleepTime, bool showLoadingText[], int loadingSize, char normalChar[], char specialChar[]);

#endif