#include "gameLogic.h"

int firstPlayerChoice;

int secondPlayerChoice;

int turnCount = 0;

int GameMenu(){
	PrintFunctions(6, 0, "0- Pedra;");
	PrintFunctions(0, 0, "\n1- Papel;");
	PrintFunctions(0, 0, "\n2- Tesoura;");
	PrintFunctions(0, 0, "\n//-:");
}

int ResetTurnCount(){
	turnCount = 0;
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