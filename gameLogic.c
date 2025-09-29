#include "gameLogic.h"

int firstPlayerChoice, secondPlayerChoice, turnCount;

int GameMenu(){
		PrintFunctions(6, 0, "0- Pedra;");
		PrintFunctions(0, 0, "\n1- Papel;");
		PrintFunctions(0, 0, "\n2- Tesoura;");
		PrintFunctions(0, 0, "\n//-:");
}

int GetPlayerInput(){
	if(turnCount == 0)
	{
		scanf("%d", &firstPlayerChoice);
	}
	else
	{
		scanf("%d", &secondPlayerChoice);
	}
}

int GetCPUInput(){
	srand(time(NULL)); ///SRAND PRECISA INICIALIZAR COM UMA SEED FIXA PRA GERAR OS NÚMEROS. POREM COMO ISSO FICA HORRIVEL, COLOCASE TIME ALI
	
	secondPlayerChoice = rand() % 3; //ESSA PORCENTAGEM + NUMERO EH O VALOR MAXIMO PARA A GERACAO MAS N EH INCLUSIVO
	
	//printf("\n\n%d ", secondPlayerChoice); //ISSO AQUI EH SO PRA DEBUG

	switch(secondPlayerChoice){
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
}

//ESCOLHI PEDRA, O CPU TESOURA E ELE GANHOU WTF

int CompareChoicesAndDefineWinner(int menupart){ //0 ganha de 2 -||- 2 ganha de 1 -||- 1 ganha de 0

	turnCount = 0;
	
	if(firstPlayerChoice == secondPlayerChoice)
	{
		PrintFunctions(1, 3000, "\n\nEMPATE!");
	}
	else if(firstPlayerChoice < 2)
	{
		if(firstPlayerChoice == 0 && secondPlayerChoice == 2)//JOGADOR GANHOU
		{	
			if(menupart == 1){
				WinnerDisplay(1);
			}
		}
		else if(secondPlayerChoice > firstPlayerChoice)//CPU GANHOU
		{
			if(menupart == 1){
				WinnerDisplay(0);
			}
		}
		else//JOGADOR GANHOU
		{
			if(menupart == 1){
				WinnerDisplay(1);
			}
		}
		
		return 1;
	}
	else
	{
		if(secondPlayerChoice == 0)//CPU GANHOU
		{
			if(menupart == 1){
				WinnerDisplay(0);
			}
		}
		else//JOGADOR GANHOU
		{
			if(menupart == 1){
				WinnerDisplay(1);
			}
		}
		
		return 1;
	}
	
	return 0;
}

int WinnerDisplay(int displayIndex)
{	
	char stringToDisplay[] = "GANHOU!";
	
	switch(displayIndex)
	{
		case 0: ; //PESQUISAR PORQUE PRECISA DESSA PORRA
			char nameToDisplay[15] = "\n\nCPU ";
			strcat(nameToDisplay, stringToDisplay);
			PrintFunctions(1, 3000, nameToDisplay);
		break;
		case 1:
			nameToDisplay[15] = "\n\nJOGADOR ";
			strcat(nameToDisplay, stringToDisplay);
			PrintFunctions(1, 3000, nameToDisplay);
		break;
		case 2:
			nameToDisplay[15] = "\n\nJOGADOR 1 ";
			strcat(nameToDisplay, stringToDisplay);
			PrintFunctions(1, 3000, nameToDisplay);
		break;				
		case 3:
			nameToDisplay[15] = "\n\nJOGADOR 2 ";
			strcat(nameToDisplay, stringToDisplay);
			PrintFunctions(1, 3000, nameToDisplay);
		break;	
	    /*case 4:
			char nameToDisplay[] = "\n\n";
			strcat(nameToDisplay, specificName);
			strcat(nameToDisplay, stringToDisplay);
			PrintFunctions(1, 3000, nameToDisplay);
		break;*/	
	}
}