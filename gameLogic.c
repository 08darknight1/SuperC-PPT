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

int GameMenu(){
	PrintFunctions(6, 0, "0- Pedra;");
	PrintFunctions(0, 0, "\n1- Papel;");
	PrintFunctions(0, 0, "\n2- Tesoura;");
	PrintFunctions(0, 0, "\n//-:");
}

int ResetTurnCount(){
	turnCount = 0;
}

int SetupTournament(){
	while(bestOfMatches%2 == 0 || bestOfMatches <= 0)
	{
		PrintFunctions(2, 2000, "Quantos rounds serao disputados entre os 2 concorrentes?");
		
		PrintFunctions(0, 0, "\n//-:");
	
		scanf("%d", &bestOfMatches);
	}
	
	float productOfNOP = 0;
	
	char nameOfPlayers[700][700] = {0};
	
	do
	{
		bool keepTheLoopGoing = true;
			
		PrintFunctions(2, 2000, "Quantos jogadores estarao disputando o Torneio?");
		
		PrintFunctions(0, 0, "\n//-:");
	
		scanf("%d", &numberOfPlayers);
		
		/* Texto de debug
		char productOFNOPSTRING[500] = "";
		
		char numberOfPlayersString[] = "";
	
		sprintf(numberOfPlayersString, "%d", numberOfPlayers);
	
		printf("%s", numberOfPlayersString);
		
		PrintFunctions(1, 10000, "\n//-:");*/
		
		productOfNOP = numberOfPlayers/2;
		
		while(keepTheLoopGoing)
		{
			/* Texto de debug
			sprintf(productOFNOPSTRING, "%f", productOfNOP);
			printf("\n Product of NOP: %s", &productOFNOPSTRING);
			PrintFunctions(1, 1000, "");
			*/
		
			float testOperation = productOfNOP/2;
			
			/*Texto de debug
			char testOperationString[500] = "";
			
			sprintf(testOperationString, "%f", testOperation);
			
			printf("\n Test Operation before adding to Product of NOP: %s", &testOperationString);
			PrintFunctions(1, 1000, "");*/
			
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
	while(numberOfPlayers%2==1 || numberOfPlayers <= 1 || productOfNOP>1);
	
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
		
		PrintFunctions(2, 1000, fullTextString); //Printa a pergunta completa para o usuário
		PrintFunctions(0, 0, "\n0.Nao");
		PrintFunctions(0, 0, "\n1.Sim");
		PrintFunctions(0, 0, "\n//-:");
		
		int isCPUorNot = 0;
		
		scanf("%d", &isCPUorNot);
		
		playerIsCPU[cont] = isCPUorNot;
		
		char nameToRegister[500] = "";
		
		int nameToRegisterLength = 0;
		
		if(isCPUorNot == 0)
		{
			PrintFunctions(2, 1000, "Qual sera o nome do jogador?");
			PrintFunctions(0, 0, "\n//-:");
			
			getchar();
				
			fgets(nameOfPlayers[cont], sizeof(nameOfPlayers[cont]), stdin);
			nameOfPlayers[cont][strlen(nameOfPlayers[cont]) - 1] = "\0";
			
			//scanf("%s", &nameOfPlayers[cont]);
		}
		else
		{
			char playerID[500] = "";
			
			nameToRegister[700] = "CPU-";
			
			sprintf(playerID, "%d", cont);
			
			strcat(nameToRegister, playerID);
			
			strlen(nameToRegister);
			
			for(int x = 0; x < nameToRegisterLength; x++)
			{	
				nameOfPlayers[cont][x] = nameToRegister[x];
			}
		}
	}
}

int PlayTournament()
{
	int cont = 0;
	
	char numberOfPlayersString[500] = "";
	
	sprintf(numberOfPlayersString, "%d", numberOfPlayers);
	
	printf("%s", numberOfPlayersString);
		
	PrintFunctions(1, 5000, "\nFoi esse o número certo de jogadores?");
		
	for(cont; cont < numberOfPlayers; cont++)
	{	
		printf("%s", nameOfPlayers[cont]);
		printf("\n");
		Sleep(3000);
		/*
		int x = 0;
		
		for(x; x < strlen(nameOfPlayers[cont]); x++)
		{
			printf("%s", nameOfPlayers[cont][x]);
			Sleep(2000);
		}
		
		printf("\n");*/
	}
	
	/*
	int cont = 0;
	
	PrintFunctions(2, 2000, "Bem vindos ao mais novo TORNEIO P. P. T!!!");
	
	PrintFunctions(2, 2000, "Nesta edicao, teremos os seguintes concorrentes: ");	
			
	for(cont; cont < numberOfPlayers; cont++)
	{	
		char firstpart[500] = "Player: ";
		
		strcat(firstpart, nameOfPlayers[cont][0]);
		
		PrintFunctions(0, 200, firstpart);
	}*/
}

int GetPlayerInput(int gamemode)
{
	//printf("%s", turnCount);
				
	if(turnCount == 0)
	{
		scanf("%d", &firstPlayerChoice);
		
		if(gamemode == 0)
		{
			PrintPlayersChoice(1);
		}
	}
	else
	{
		scanf("%d", &secondPlayerChoice);
		if(gamemode == 1)
		{
			PrintPlayersChoice(2);
			PrintPlayersChoice(3);
		}				
	}
	
	turnCount++;	
}

int GetCPUInput(){
	srand(time(NULL)); ///SRAND PRECISA INICIALIZAR COM UMA SEED FIXA PRA GERAR OS NÚMEROS. POREM COMO ISSO FICA HORRIVEL, COLOCASE TIME ALI
	
	secondPlayerChoice = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO
	
	PrintPlayersChoice(0);
}

//ESCOLHI PEDRA, O CPU TESOURA E ELE GANHOU WTF

int DefineWinner(int menupart){ //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0

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
				WinnerDisplay(1); //DISPLAY: JOGADOR GANHOU
			}
			else
			{
				WinnerDisplay(2); //DISPLAY: JOGADOR 1 GANHOU
			}	
		}
		else if(secondPlayerChoice == 1)
		{		
			if(menupart == 1)
			{
				WinnerDisplay(0); //DISPLAY: CPU GANHOU
			}
			else
			{
				WinnerDisplay(3); //DISPLAY: JOGADOR 2 GANHOU
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
				WinnerDisplay(1); //DISPLAY: JOGADOR GANHOU
			}
			else
			{
				WinnerDisplay(2); //DISPLAY: JOGADOR 1 GANHOU
			}	
		}
		else if(secondPlayerChoice == 2)
		{		
			if(menupart == 1)
			{
				WinnerDisplay(0); //DISPLAY: CPU GANHOU
			}
			else
			{
				WinnerDisplay(3); //DISPLAY: JOGADOR 2 GANHOU
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
				WinnerDisplay(1); //DISPLAY: JOGADOR GANHOU
			}
			else
			{
				WinnerDisplay(2); //DISPLAY: JOGADOR 1 GANHOU
			}	
		}
		else if(secondPlayerChoice == 0)
		{		
			if(menupart == 1)
			{
				WinnerDisplay(0); //DISPLAY: CPU GANHOU
			}
			else
			{
				WinnerDisplay(3); //DISPLAY: JOGADOR 2 GANHOU
			}
		}
		
		return 1;
	}
	
	return 0;
}

int WinnerDisplay(int displayIndex)
{	
	char stringToDisplay[] = "GANHOU!";
	
	char name0[] = "\n\nCPU ";
	char name1[] = "\n\nJOGADOR ";
	char name2[] = "\n\nJOGADOR 1 ";
	char name3[] = "\n\nJOGADOR 2 ";
	
	char nameToDisplay[500] = "";
	
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
	}
	
	strcat(nameToDisplay, stringToDisplay);
	
	PrintFunctions(1, 3000, nameToDisplay);
}

int PrintPlayersChoice(int player)
{	
	switch(player)
	{	
		case 0://PRINT CPU
			switch(secondPlayerChoice)	
			{
				case 0:
					PrintFunctions(1, 2000, "\n\nCPU ESCOLHEU PEDRA!"); 
	    		break;		
				case 1:
					PrintFunctions(1, 2000, "\n\nCPU ESCOLHEU PAPEL!"); 
	    		break;
				case 2:
					PrintFunctions(1, 2000, "\n\nCPU ESCOLHEU TESOURA!"); 
	    		break;	
			}			  
		break;  
		case 1://PRINT JOGADOR
			switch(firstPlayerChoice)
			{
				case 0:
					PrintFunctions(1, 2000, "\n\nJOGADOR ESCOLHEU PEDRA!"); 
	   			break;		
				case 1:
					PrintFunctions(1, 2000, "\n\nJOGADOR ESCOLHEU PAPEL!"); 
	   			break;
				case 2:
					PrintFunctions(1, 2000, "\n\nJOGADOR ESCOLHEU TESOURA!"); 
	    		break;			    
			}		  
		break;
		case 2://PRINT JOGADOR 1
	  		switch(firstPlayerChoice)
			{
				case 0:
					PrintFunctions(1, 2000, "\n\nJOGADOR 1 ESCOLHEU PEDRA!"); 
	   			break;		
				case 1:
					PrintFunctions(1, 2000, "\n\nJOGADOR 1 ESCOLHEU PAPEL!"); 
	   			break;
				case 2:
					PrintFunctions(1, 2000, "\n\nJOGADOR 1 ESCOLHEU TESOURA!"); 
	    		break;			    
			}
		break;	
		case 3://PRINT JOGADOR 2
	  	  	switch(secondPlayerChoice)
			{
				case 0:
					PrintFunctions(1, 2000, "\n\nJOGADOR 2 ESCOLHEU PEDRA!"); 
	   			break;		
				case 1:
					PrintFunctions(1, 2000, "\n\nJOGADOR 2 ESCOLHEU PAPEL!"); 
	   			break;
				case 2:
					PrintFunctions(1, 2000, "\n\nJOGADOR 2 ESCOLHEU TESOURA!"); 
	    		break;			    
			}
		break;
	}
}