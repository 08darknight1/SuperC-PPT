#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

int GameMenu();

int ResetTurnCount();

int SetupTournament();

int PlayTournament();

int GetPlayerInput(int gamemode, char nameOfPlayer[]);

int GetCPUInput(char CpuName[], int playerTurn);

int DefineWinner(int menupart, char firstPlayerName[], char secondPlayerName[]);

int WinnerDisplay(int displayIndex, char firstPlayerName[], char secondPlayerName[]);

int PrintPlayersChoice(char nameToPrint[], int choice);

#endif