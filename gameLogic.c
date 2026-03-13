#include "gameLogic.h"

#include <stdio.h>

//VARs para o gameplay no geral

int firstPlayerChoice;

int secondPlayerChoice;

int turnCount = 0;

//VARs para o modo torneio

int bestOfMatches;

int numberOfPlayers;

char nameOfPlayers[500][500];

bool playerEliminated[500];

int playerIsCPU[500];

int playersWinsCount[2];

int GameMenu(){
	PrintFunctions(6, 0, "0- Pedra;");
	PrintFunctions(0, 0, "\n1- Papel;");
	PrintFunctions(0, 0, "\n2- Tesoura;");
	PrintFunctions(0, 0, "\n//-:");
}

int ResetTurnCount(){
	turnCount = 0;
}

int SetupTournament()
{		
	while(bestOfMatches%2 == 0 || bestOfMatches <= 0 || bestOfMatches > 9)
	{
		PrintFunctions(2, 2000, "Quantos rounds serao disputados entre os 2 concorrentes? (1 - 3 - 5 - 7 - 9)");
		
		PrintFunctions(0, 0, "\n//-:");
	
		scanf("%d", &bestOfMatches);
	}
	
	float productOfNOP = 0;
	
	do
	{
		bool keepTheLoopGoing = true;
			
		PrintFunctions(2, 2000, "Quantos jogadores estarao disputando o Torneio? (2 - 4 - 8 - 16 - 32 - 64 - 128)");
		
		PrintFunctions(0, 0, "\n//-:");
	
		scanf("%d", &numberOfPlayers);
		
		productOfNOP = numberOfPlayers/2;
		
		while(keepTheLoopGoing)
		{		
			float testOperation = productOfNOP/2;
			
			if(testOperation < 1)
			{	
				keepTheLoopGoing = false;	
			}
			else
			{
				productOfNOP = testOperation;	
			}
		}
	}
	while(numberOfPlayers%2==1 || numberOfPlayers <= 1 || productOfNOP>1 || numberOfPlayers > 128);
	
	int cont = 0;
	
	for(cont; cont < numberOfPlayers; cont++)
	{	
		char contButInString [500] = "";
		
		char fullTextString [500] = "O combatente ";
	
		char restOfPhrase [500] = " sera uma CPU?";
	
		//PrintFunctions(1, 2000, contButInString);
		
		sprintf(contButInString, "%d", cont);
		
		strcat(fullTextString, contButInString);
		
		strcat(fullTextString, restOfPhrase);
		
		int isCPUorNot = 0;
		
		PrintFunctions(2, 1000, fullTextString); //Printa a pergunta completa para o usuário
		PrintFunctions(0, 0, "\n0.Nao");
		PrintFunctions(0, 0, "\n1.Sim");
		PrintFunctions(0, 0, "\n//-:");
		
		scanf("%d", &isCPUorNot);
		
		playerIsCPU[cont] = isCPUorNot;
		
		if(isCPUorNot == 0)
		{
			PrintFunctions(2, 1000, "Qual sera o nome do jogador?");
			PrintFunctions(0, 0, "\n//-:");
			scanf("%s", &nameOfPlayers[cont]);
		}
		else
		{
			char playerID[500] = ""; //cria uma var para pegar o ID do player que esta sendo registrado agora
			
			char CpuNameToRegister[500] = "CPU-"; //cria uma var com o prefixo dos jogadores de CPU
			
			sprintf(playerID, "%d", cont); //Adiciona o valor de cont pra criar o player ID da nova CPU sendo registrada
			
			strcat(CpuNameToRegister, playerID); //Adiciona o player ID no CPUName pra criar o nome completo dela		
			
			int nameToRegisterLength = 0; //Var inicializada pra ter facil acesso ao tamanho do CPUName
					
			nameToRegisterLength = strlen(CpuNameToRegister); //Finalmente aloca o tamanho atual do CPUName para a variavel
			
			/*
			char NTRLInString[500] = ""; //Mais uma var de char pra print que n existe mais
			
			sprintf(NTRLInString, "%d", nameToRegisterLength); //Colocando o valor do length em uma string pra um print que não existe mais
			*/
			
			strncpy(nameOfPlayers[cont], CpuNameToRegister, nameToRegisterLength);
		}
	}
}

int PlayTournament()
{
	int playerIndex = 0;
	
	bool tournamentStillGoing = true;
	
	int playersSelectedArray[2] = {0, 0}; 
	
	while(tournamentStillGoing)
	{	
		PrintFunctions(2, 2000, "Proximo Confronto: ");
		
		int playersSelected = 0;
		
		playersWinsCount[0] = 0;
	
		playersWinsCount[1] = 0;
	
		for(int x = 0; x < numberOfPlayers; x++)
		{	
			if(!playerEliminated[x])
			{
				playersSelectedArray[playersSelected] = playerIndex;
				playersSelected++;
				PrintFunctions(1, 1000, nameOfPlayers[playerIndex]);
			}
			
			if(playersSelected >= 2)
			{
				break;
			}
			else if(playersSelected == 1)
			{
				PrintFunctions(1, 1000, " X ");
			}
			
			playerIndex++;
		}
		
		PrintFunctions(5, 0, "");
		
		for(int x = 0; x < bestOfMatches; x++)
		{
			if(x >= 1)
			{
				char player0StringWin[] = "100";
				char player1StringWin[] = "100";
				
				sprintf(player0StringWin, "%d", playersWinsCount[0]);
				sprintf(player1StringWin, "%d", playersWinsCount[1]);
				
				PrintFunctions(2, 500, nameOfPlayers[playersSelectedArray[0]]);
				PrintFunctions(1, 500, " (");
				PrintFunctions(1, 500, player0StringWin);
				PrintFunctions(1, 500, ")-");
				PrintFunctions(1, 500, "X");
				PrintFunctions(1, 500, "-(");
				PrintFunctions(1, 500, player1StringWin);
				PrintFunctions(1, 500, ") ");
				PrintFunctions(1, 3000, nameOfPlayers[playersSelectedArray[1]]);
			}
					
			turnCount = 0;
		
			bool winnerForRoundDecided = false;
		
			while(!winnerForRoundDecided)
			{
				if(playerIsCPU[playersSelectedArray[turnCount]])
				{	
					GetCPUInput(nameOfPlayers[playersSelectedArray[turnCount]], turnCount);
					turnCount++;
				}
				
				if(turnCount >= 2)
				{
					int winner = DefineWinner(3, nameOfPlayers[playersSelectedArray[0]], nameOfPlayers[playersSelectedArray[1]] );
				
					if(winner >= 1)
					{
						winnerForRoundDecided = true;
					}
					else
					{
						turnCount = 0;	
					}
				}
			}	
		}
	}
}

int GetPlayerInput(int gamemode, char nameOfPlayer[])
{
	//printf("%s", turnCount);
				
	if(turnCount == 0)
	{
		scanf("%d", &firstPlayerChoice);
		
		if(gamemode == 0)
		{
			PrintPlayersChoice(nameOfPlayer, firstPlayerChoice);
		}
	}
	else
	{
		scanf("%d", &secondPlayerChoice);
		
		/* Precisa refazer como ele faz o display de quando é player contra player
		if(gamemode == 1)
		{
			PrintPlayersChoice(2);
			PrintPlayersChoice(3);
		}			
		*/	
	}
	
	turnCount++;	
}

int GetCPUInput(char CpuName[], int playerTurn){
	srand(time(NULL)); ///SRAND PRECISA INICIALIZAR COM UMA SEED FIXA PRA GERAR OS NÚMEROS. POREM COMO ISSO FICA HORRIVEL, COLOCASE TIME ALI
	
	if(playerTurn == 1)
	{
		secondPlayerChoice = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO
		PrintPlayersChoice(CpuName, secondPlayerChoice);
	}
	else
	{
		firstPlayerChoice = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO		
		PrintPlayersChoice(CpuName, firstPlayerChoice);
	}
}

//ESCOLHI PEDRA, O CPU TESOURA E ELE GANHOU WTF

int DefineWinner(int menupart, char firstPlayerName[], char secondPlayerName[]){ //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0

	turnCount = 0;
	
	if(firstPlayerChoice == secondPlayerChoice)
	{
		PrintFunctions(1, 3000, "\n\nEMPATE!");
	}
	else if(firstPlayerChoice == 0)
	{

		if(secondPlayerChoice == 2) //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0
		{
			if(menupart == 1)
			{
				WinnerDisplay(1, "", ""); //DISPLAY: JOGADOR GANHOU
			}
			else if(menupart == 2)
			{
				WinnerDisplay(2, "", ""); //DISPLAY: JOGADOR 1 GANHOU
			}
			else if(menupart == 3)
			{
				WinnerDisplay(4, firstPlayerName, ""); //DISPLAY NOME CUSTOMIZADO DO JOGADOR 1
			 	playersWinsCount[0]++;
			}
		}
		else if(secondPlayerChoice == 1)
		{		
			if(menupart == 1)
			{
				WinnerDisplay(0, "", ""); //DISPLAY: CPU GANHOU
			}
			else if(menupart == 2)
			{
				WinnerDisplay(3, "", ""); //DISPLAY: JOGADOR 2 GANHOU
			}
			else if(menupart == 3)
			{
				WinnerDisplay(5, "", secondPlayerName); //DISPLAY NOME CUSTOMIZADO DO JOGADOR 2
			 	playersWinsCount[1]++;
			}
		}	
			
		return 1;
	}
	else if(firstPlayerChoice == 1)
	{
		if(secondPlayerChoice == 0) //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0
		{
			if(menupart == 1)
			{
				WinnerDisplay(1, "", ""); //DISPLAY: JOGADOR GANHOU
			}
			else if(menupart == 2)
			{
				WinnerDisplay(2, "", ""); //DISPLAY: JOGADOR 1 GANHOU
			}	
			else if(menupart == 3)
			{
				WinnerDisplay(4, firstPlayerName, ""); //DISPLAY: JOGADOR 1 GANHOU
			 	playersWinsCount[0]++;
			}
		}
		else if(secondPlayerChoice == 2)
		{		
			if(menupart == 1)
			{
				WinnerDisplay(0, "", ""); //DISPLAY: CPU GANHOU
			}
			else if(menupart == 2)
			{
				WinnerDisplay(3, "", ""); //DISPLAY: JOGADOR 2 GANHOU
			}
			else if(menupart == 3)
			{
				WinnerDisplay(5, "", secondPlayerName);
			 	playersWinsCount[1]++;
			}
		}
				
		return 1;
	}
	else if(firstPlayerChoice == 2)
	{
		if(secondPlayerChoice == 1) //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0
		{
			if(menupart == 1)
			{
				WinnerDisplay(1, "", ""); //DISPLAY: JOGADOR GANHOU
			}
			else if(menupart == 2)
			{
				WinnerDisplay(2, "", ""); //DISPLAY: JOGADOR 1 GANHOU
			}	
			else if(menupart == 3)
			{
				WinnerDisplay(4, firstPlayerName, "");
			 	playersWinsCount[0]++;
			}
		}
		else if(secondPlayerChoice == 0)
		{		
			if(menupart == 1)
			{
				WinnerDisplay(0, "", ""); //DISPLAY: CPU GANHOU
			}
			else if(menupart == 2)
			{
				WinnerDisplay(3, "", ""); //DISPLAY: JOGADOR 2 GANHOU
			}
			else if(menupart == 3)
			{
				WinnerDisplay(5, "", secondPlayerName);
			 	playersWinsCount[1]++;
			}
		}		
		return 1;
	}
	
	return 0;
}

int WinnerDisplay(int displayIndex, char firstPlayerName[], char secondPlayerName[])
{	
	char stringToDisplay[] = " GANHOU!";
	
	char name0[] = "\n\nCPU ";
	char name1[] = "\n\nJOGADOR ";
	char name2[] = "\n\nJOGADOR 1";
	char name3[] = "\n\nJOGADOR 2";
	char name4[] = "\n\n";
	char name5[] = "\n\n";
	
	strcpy(name4, firstPlayerName);
	
	strcpy(name5, secondPlayerName);
	
	char nameToDisplay[500] = "\n\n";
	
	switch(displayIndex)
	{
		case 0:
			strcat(nameToDisplay, name0);
		break;
		case 1:
			strcat(nameToDisplay, name1);
		break;
		case 2:
			strcat(nameToDisplay, name2);
		break;
		case 3:
			strcat(nameToDisplay, name3);
		break;
		case 4:
			strcat(nameToDisplay, name4);
		break;
		case 5:
			strcat(nameToDisplay, name5);
		break;
	}
	
	strcat(nameToDisplay, stringToDisplay);
	
	PrintFunctions(1, 3000, nameToDisplay);
}

int PrintPlayersChoice(char nameToPrint[], int choice)
{	
	char choiceInText[500] = "";
	
	switch(choice)
	{
		case 0:
			strcpy(choiceInText, "PEDRA!");
		break;
		case 1:
			strcpy(choiceInText, "PAPEL!");
		break;
		case 2:
			strcpy(choiceInText, "TESOURA!");
		break;	
	}
	
	char middleWord[500] = " escolheu ";
	
	char completePhrase[500] = "";
	
	strcat(completePhrase, nameToPrint);
	
	strcat(completePhrase, middleWord);
	
	strcat(completePhrase, choiceInText);
	
	PrintFunctions(2, 2000, completePhrase); 
}