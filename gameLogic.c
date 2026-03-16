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

int lastOptionRandomized;

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
	bool tournamentStillGoing = true;
	
	int playersSelectedArray[2] = {0, 0};
	
	for(int x = 0; x < sizeof(playerEliminated); x++)
	{
		playerEliminated[x] = false;	
	}
	
	int playersSelected = 0;
	
	while(tournamentStillGoing)
	{				
		for(int x = 0; x < numberOfPlayers; x++)
		{	
			if(!playerEliminated[x])
			{
				playersSelectedArray[playersSelected] = x;
				playersSelected++;
			}
			
			if(playersSelected >= 2)
			{
				PrintFunctions(2, 2000, "Proximo Confronto: ");
				PrintFunctions(1, 1000, nameOfPlayers[playersSelectedArray[0]]);
				PrintFunctions(1, 1000, " X ");
				PrintFunctions(1, 1000, nameOfPlayers[playersSelectedArray[1]]);
				
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
			
					while(!winnerForRoundDecided)
					{				
						if(playerIsCPU[playersSelectedArray[turnCount]])
						{	
							GetCPUInput(3, nameOfPlayers[playersSelectedArray[turnCount]], turnCount);
							turnCount++;
						}
						else
						{	
							char messageToPrint[500] = "";
					
							strcat(messageToPrint, "Chegou sua vez ");
					
							strcat(messageToPrint, nameOfPlayers[playersSelectedArray[turnCount]]);
					
							strcat(messageToPrint, "!!!");
					
							PrintFunctions(2, 2000, messageToPrint);
					
							GameMenu();

							GetPlayerInput(3, nameOfPlayers[playersSelectedArray[turnCount]]);
						}
				
						if(turnCount >= 2)
						{
							PrintPlayersChoice(nameOfPlayers[playersSelectedArray[0]], firstPlayerChoice);
							PrintPlayersChoice(nameOfPlayers[playersSelectedArray[1]], secondPlayerChoice);
				
							int winner = DefineRoundWinner(3, nameOfPlayers[playersSelectedArray[0]], nameOfPlayers[playersSelectedArray[1]]);
				
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
			
			strcat(winnerName, nameOfPlayers[playersSelectedArray[0]]);
			
			strcat(winnerName, "!!!");
			
			PrintFunctions(1, 2000, winnerName);
			
			PrintFunctions(1, 0, "\n\n");
			
			char finalMessage[300] = "Obrigado a todos por participar e novamente parabens a ";
			
			strcat(finalMessage, nameOfPlayers[playersSelectedArray[0]]);
			
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
			
	PrintFunctions(2, 500, nameOfPlayers[playerArray[0]]);
	PrintFunctions(1, 500, " (");
	PrintFunctions(1, 500, player0StringWin);
	PrintFunctions(1, 500, ")-");
	PrintFunctions(1, 500, "X");
	PrintFunctions(1, 500, "-(");
	PrintFunctions(1, 500, player1StringWin);
	PrintFunctions(1, 500, ") ");
	PrintFunctions(1, 3000, nameOfPlayers[playerArray[1]]);
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
		
		if(gamemode == 1)
		{
			PrintPlayersChoice("JOGADOR 1", firstPlayerChoice);
			PrintPlayersChoice("JOGADOR 2", secondPlayerChoice);
		}				
	}
	
	turnCount++;	
}

int GetCPUInput(int gamemode, char CpuName[], int playerTurn){
	srand(time(NULL)); ///SRAND PRECISA INICIALIZAR COM UMA SEED FIXA PRA GERAR OS NÚMEROS. POREM COMO ISSO FICA HORRIVEL, COLOCASE TIME ALI
	
	if(playerTurn == 1)
	{
		while(secondPlayerChoice == lastOptionRandomized)
		{
			secondPlayerChoice = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO
		
			if(gamemode != 3)
			{
				PrintPlayersChoice(CpuName, secondPlayerChoice);
			}
		}
		
		lastOptionRandomized = secondPlayerChoice;
	}
	else
	{		
		while(firstPlayerChoice == lastOptionRandomized)
		{
			firstPlayerChoice = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO
					
			if(gamemode != 3)
			{
				PrintPlayersChoice(CpuName, firstPlayerChoice);
			}
		}
				
		lastOptionRandomized = firstPlayerChoice;
	}
}

//ESCOLHI PEDRA, O CPU TESOURA E ELE GANHOU WTF

int DefineRoundWinner(int menupart, char firstPlayerName[], char secondPlayerName[]){ //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0

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
		playerEliminated[playerArray[1]] = true;
		strcat(winnerName, nameOfPlayers[playerArray[0]]);
	}
	else if(playersWinsCount[1] >= winningNumber)
	{
		playerEliminated[playerArray[0]] = true;
		strcat(winnerName, nameOfPlayers[playerArray[1]]);
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