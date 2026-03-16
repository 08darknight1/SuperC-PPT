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

int ShowCurrentScore(int playerArray[]);

int GetCPUInput(int gamemode, char CpuName[], int playerTurn);

int DefineRoundWinner(int menupart, char firstPlayerName[], char secondPlayerName[]);

int DefineMatchWinner(int playerArray[]);

int WinnerDisplay(int displayIndex, char firstPlayerName[], char secondPlayerName[]);

int PrintPlayersChoice(char nameToPrint[], int choice);

#endif