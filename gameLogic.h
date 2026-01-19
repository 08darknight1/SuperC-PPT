#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

int GameMenu();

int ResetTurnCount();

int GetPlayerInput(int gamemode);

int GetCPUInput();

int DefineWinner();

int WinnerDisplay(int displayIndex);

int PrintPlayersChoice(int player);

#endif