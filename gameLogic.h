#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

int GameMenu();

int GetPlayerInput();

int GetCPUInput();

int CompareChoicesAndDefineWinner();

int WinnerDisplay();

#endif