#include "gameLogic.h"
#include "playerProfile.h"

#include <stdio.h>

//VARs para o gameplay no geral

int playersChoice[2];

int turnCount = 0;

//VARs para o modo torneio

int bestOfMatches;

int numberOfPlayers;

//char nameOfPlayers[500][500]; //Tenho que remover

//bool playerEliminated[500]; //Tenho que remover

//int playerIsCPU[500]; //Tenho que remover

struct Player totalPlayers[];

int playersWinsCount[2];

int lastOptionRandomized;

bool cpuAlreadyPlayed = false;

int GameMenu(){
	/*if(playersChoice[0] == NULL || playersChoice[1] == NULL)
	{
		playersChoice[0] = -1;
		playersChoice[1] = -1;
	}*/
	
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
	
	totalPlayers[numberOfPlayers];
	
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
		
		if(isCPUorNot == 1)
		{
			totalPlayers[cont].PlayerIsCPU = true;
		}
		
		if(isCPUorNot == 0)
		{
			totalPlayers[cont].PlayerIsCPU = false;
			PrintFunctions(2, 1000, "Qual sera o nome do jogador?");
			PrintFunctions(0, 0, "\n//-:");
			scanf("%s", &totalPlayers[cont].PlayerName);
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
			
			strncpy(totalPlayers[cont].PlayerName, CpuNameToRegister, nameToRegisterLength);
		}
	}
}

int PlayTournament()
{
	bool tournamentStillGoing = true;
	
	int playersSelectedArray[2] = {0, 0};
	
	for(int x = 0; x < numberOfPlayers; x++)
	{
		totalPlayers[x].PlayerEliminated = false;	
	}
	
	int playersSelected = 0;
	
	while(tournamentStillGoing)
	{				
		for(int x = 0; x < numberOfPlayers; x++)
		{	
			if(!totalPlayers[x].PlayerEliminated)
			{
				playersSelectedArray[playersSelected] = x;
				playersSelected++;
			}
			
			if(playersSelected >= 2)
			{
				PrintFunctions(2, 2000, "Proximo Confronto: ");
				PrintFunctions(1, 1000, totalPlayers[playersSelectedArray[0]].PlayerName);
				PrintFunctions(1, 1000, " X ");
				PrintFunctions(1, 1000, totalPlayers[playersSelectedArray[1]].PlayerName);
				
				PrintFunctions(5, 0, "");
		
				for(int y = 0; y < bestOfMatches; y++)
				{	
					if(y >= 1)
					{
						ShowCurrentScore(playersSelectedArray);
					}
					
					int winningNumber = 0;
			
					winningNumber = (bestOfMatches/2) + 1;
			
					if(playersWinsCount[0] >= winningNumber || playersWinsCount[1] >= winningNumber)
					{
						break;
					}
			
					turnCount = 0;
		
					bool winnerForRoundDecided = false;
					
					cpuAlreadyPlayed = false;
			
					while(!winnerForRoundDecided)
					{				
						if(totalPlayers[playersSelectedArray[turnCount]].PlayerIsCPU)
						{	
							GetCPUInput(3, totalPlayers[playersSelectedArray[turnCount]].PlayerName, turnCount);
							turnCount++;
						}
						else
						{	
							char messageToPrint[500] = "";
					
							strcat(messageToPrint, "Chegou sua vez ");
					
							strcat(messageToPrint, totalPlayers[playersSelectedArray[turnCount]].PlayerName);
					
							strcat(messageToPrint, "!!!");
					
							PrintFunctions(2, 2000, messageToPrint);
					
							GameMenu();

							GetPlayerInput(3, totalPlayers[playersSelectedArray[turnCount]].PlayerName);
						}
				
						if(turnCount >= 2)
						{
							PrintPlayersChoice(totalPlayers[playersSelectedArray[0]].PlayerName, playersChoice[0]);
							PrintPlayersChoice(totalPlayers[playersSelectedArray[1]].PlayerName, playersChoice[1]);
				
							int winner = DefineRoundWinner(3, totalPlayers[playersSelectedArray[0]].PlayerName, totalPlayers[playersSelectedArray[1]].PlayerName);
				
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
				
				DefineMatchWinner(playersSelectedArray);
				playersSelected = 0;
			}
		}
		
		//aqui coloca aquele ifzão que se tiver só 1 no playerselected, esse querido é o vencedor do torneio
		
		if(playersSelected == 1)
		{
			PrintFunctions(2, 1000, "E finalmente temos o grande vencedor do torneio!");
			
			PrintFunctions(1, 2000, " Uma salva de palmas para... ");
			
			char winnerName[50] = "\n\n";
			
			strcat(winnerName, totalPlayers[playersSelectedArray[0]].PlayerName);
			
			strcat(winnerName, "!!!");
			
			PrintFunctions(1, 2000, winnerName);
			
			PrintFunctions(1, 0, "\n\n");
			
			char finalMessage[300] = "Obrigado a todos por participar e novamente parabens a ";
			
			strcat(finalMessage, totalPlayers[playersSelectedArray[0]].PlayerName);
			
			strcat(finalMessage, " pela incrivel gameplay!");
			
			PrintFunctions(1, 6000, finalMessage);
			
			tournamentStillGoing = false;
			
			break;
		}
	}
}

int ShowCurrentScore(int playerArray[])
{
	char player0StringWin[] = "100";
	char player1StringWin[] = "100";
				
	sprintf(player0StringWin, "%d", playersWinsCount[0]);
	sprintf(player1StringWin, "%d", playersWinsCount[1]);
			
	PrintFunctions(2, 500, totalPlayers[playerArray[0]].PlayerName);
	PrintFunctions(1, 500, " (");
	PrintFunctions(1, 500, player0StringWin);
	PrintFunctions(1, 500, ")-");
	PrintFunctions(1, 500, "X");
	PrintFunctions(1, 500, "-(");
	PrintFunctions(1, 500, player1StringWin);
	PrintFunctions(1, 500, ") ");
	PrintFunctions(1, 3000, totalPlayers[playerArray[1]].PlayerName);
}

int GetPlayerInput(int gamemode, char nameOfPlayer[])
{
	//printf("%s", turnCount);
				
	if(turnCount == 0)
	{
		scanf("%d", &playersChoice[0]);
		
		if(gamemode == 0)
		{
			PrintPlayersChoice(nameOfPlayer, playersChoice[0]);
		}
	}
	else
	{
		scanf("%d", &playersChoice[1]);
		
		if(gamemode == 1)
		{
			PrintPlayersChoice("JOGADOR 1", playersChoice[0]);
			PrintPlayersChoice("JOGADOR 2", playersChoice[1]);
		}				
	}
	
	turnCount++;	
}

int GetCPUInput(int gamemode, char CpuName[], int playerTurn){
	srand(time(NULL)); ///SRAND PRECISA INICIALIZAR COM UMA SEED FIXA PRA GERAR OS NÚMEROS. POREM COMO ISSO FICA HORRIVEL, COLOCASE TIME ALI
	
	if(playerTurn == 1)
	{
		if(cpuAlreadyPlayed)
		{
			while(playersChoice[1] == lastOptionRandomized)
			{
				playersChoice[1] = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO
			}
		}
		else
		{
			playersChoice[1] = rand() % 3;
		}

		if(gamemode != 3)
		{
			PrintPlayersChoice(CpuName, playersChoice[1]);
		}
		
		lastOptionRandomized = playersChoice[1];
	}
	else
	{		
		if(cpuAlreadyPlayed)
		{
			while(playersChoice[0] == lastOptionRandomized)
			{
				playersChoice[0] = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO
			}
		}
		else
		{
			playersChoice[0] = rand() % 3;
		}
		
		if(gamemode != 3)
		{
			PrintPlayersChoice(CpuName, playersChoice[0]);
		}
				
		lastOptionRandomized = playersChoice[0];
	}
	
	cpuAlreadyPlayed = true;
}

//ESCOLHI PEDRA, O CPU TESOURA E ELE GANHOU WTF

int DefineRoundWinner(int menupart, char firstPlayerName[], char secondPlayerName[]){ //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0

	turnCount = 0;
	/* DEBUG FOR CHOICES
	char p1Choice [2] = "";
	char p2Choice [1] = "";
		
	sprintf(p1Choice, "%d", playersChoice[0]);
	sprintf(p2Choice, "%d", playersChoice[1]);
	
	PrintFunctions(1, 3000, "\n\nDEBUG: Players choice:\n\nP1-(");
	PrintFunctions(1, 1000, p1Choice);
	PrintFunctions(1, 1000, ")\n\nP2-(");
	PrintFunctions(1, 1000, p2Choice);
	PrintFunctions(1, 10000, ")");*/
	
	if(playersChoice[0] == playersChoice[1])
	{
		PrintFunctions(1, 3000, "\n\nEMPATE!");
		return 0;
	}
	else if(playersChoice[0] == 0)
	{
		if(playersChoice[1] == 2) //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0
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
		else if(playersChoice[1] == 1)
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
	else if(playersChoice[0] == 1)
	{
		if(playersChoice[1] == 0) //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0
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
		else if(playersChoice[1] == 2)
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
	else if(playersChoice[0] == 2)
	{
		if(playersChoice[1] == 1) //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0
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
		else if(playersChoice[1] == 0)
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
	
	PrintFunctions(1, 5000, "\n\nERRO! Nenhum resultado pode ser estipulado para o confronto!");
	
	return 0;
}

int DefineMatchWinner(int playerArray[])
{
	int winningNumber = 1;
			
	if(bestOfMatches != 1)
	{
		winningNumber = (bestOfMatches/2) + 1;
	}
				
	char winnerName[50] = "";
			
	if(playersWinsCount[0] >= winningNumber)
	{	
		totalPlayers[playerArray[1]].PlayerEliminated = true;
		strcat(winnerName, totalPlayers[playerArray[0]].PlayerName);
	}
	else if(playersWinsCount[1] >= winningNumber)
	{
		totalPlayers[playerArray[0]].PlayerEliminated = true;
		strcat(winnerName, totalPlayers[playerArray[1]].PlayerName);
	}
				
	strcat(winnerName, "!!!");
				
	PrintFunctions(2, 1000, "E o vencedor eh... ");
	PrintFunctions(1, 3000, winnerName);
					
	playersWinsCount[0] = 0;
	playersWinsCount[1] = 0;
	playerArray[0] = 0;
	playerArray[1] = 1;		
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