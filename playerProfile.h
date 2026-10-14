#ifndef PLAYERPROFILE_H_INCLUDED
#define PLAYERPROFILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

struct Player{
	char PlayerName;
	bool PlayerEliminated;
	bool PlayerIsCPU;
};

#endif