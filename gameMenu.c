#include "basicFunctions.h"
#include "gameLogic.h"

int menupart = 0;
	
bool inGame = true;
	
bool loadedOptions = false;
	
int opcaoUser;


int main(){		
	system("color b");
	LoadingAnimation(500, true, 5, "-", "+");
	PrintFunctions(3, 2000, "Bem vindo ao...");
    PrintFunctions(3, 2000, "/SuperC P.P.T./Tournament Edition(V1.0)/");
    
    ///Pra voltar para o Menu, a última instrução de print ou sleep tem que dar clear no texto e mudar o loadedoptions pra false
    
    while(inGame){
    	switch(menupart){
    		case 0: //Carrega o menu principal
    			if(!loadedOptions)
				{
    				MainMenu();
    				loadedOptions = true;
   				}
   				else
				{	
				    scanf("%d", &opcaoUser);
				    if(opcaoUser < 6 && opcaoUser >= 0){
				    	menupart = opcaoUser;
					}
   				    loadedOptions = false;
				}
    		break;
    		case 1: //Carrega batalha de player contra cpu
    			if(!loadedOptions){
					GameMenu();
					loadedOptions = true;
				}
				else
				{
	    			GetPlayerInput(0);
	    			GetCPUInput();
	    			if(DefineWinner(menupart) == 1){
	    				menupart = 0;
					}
					loadedOptions = false;
				}
    		break;
    		case 2: //Carrega batalha de player contra player
    			if(!loadedOptions){
					GameMenu();
					loadedOptions = true;
				}
				else
				{
					ResetTurnCount();
	    			GetPlayerInput(1);
	    			GameMenu();
	    			GetPlayerInput(1);
	    			if(DefineWinner(menupart) == 1){
	    				menupart = 0;
					}
					loadedOptions = false;
				}
    		break;    		
    		case 4:
    			PrintFunctions(2, 4000, "Bom, meio estranho voce nao saber como jogar Pedra, Papel e Tesoura, mas vamos la...");
    			PrintFunctions(1, 3000, "\n\nMinimo de 2 jogadores, seja um outro humano ou a CPU!");
    			PrintFunctions(1, 5000, "\n\nCada um tem a chance de escolher no momento do jogo as seguintes opcoes: Pedra, Papel ou Tesoura!");
    			PrintFunctions(1, 3000, " A logica pra saber quem ganhou se baseia nessas escolhas:");
    			PrintFunctions(1, 2000, "\n\n- Pedra ganha de Tesoura...");
    			PrintFunctions(1, 2000, "\n- Tesoura ganha de Papel...");
    			PrintFunctions(1, 2000, "\n- Papel ganha de Pedra!");
    			PrintFunctions(1, 5000, "\n\nNa vida real, o pessoal mostra a opcao ao mesmo tempo, mas aqui voce escolhe antes da CPU!");
    			PrintFunctions(1, 4000, "\n\nUnica execao disso seria no modo Versus ou quando os jogadores se enfrentam no torneio...");
    			PrintFunctions(1, 3000, "\n\nVai ser pedido pra cada jogador (de verdade) escolher enquanto o outro nao olha pra tela.");
    			PrintFunctions(1, 3000, "\n\nMeio estranho mas funciona. So nao ser babaca!");
    			PrintFunctions(1, 10000, "\n\nVou deixar as intrucoes aqui por mais um tempo, mas daqui a pouco voce volta pro menu!");
    			ReturnToMainMenu();
    		break;
    		case 5:
    			PrintFunctions(4, 3000, "Muito obrigado por jogar, espero que tenha gostado e volte sempre!");
    			inGame = false;
    		break;
		}
	}
}

int MainMenu(){
		PrintFunctions(6, 2000, "/SuperC P.P.T./Tournament Edition(V1.0)/");
		PrintFunctions(0, 2000, "\n\n1.Partida contra CPU");
		PrintFunctions(0, 2000, "\n2.Partida Versus");
		PrintFunctions(0, 2000, "\n3.Torneio P.P.T.");
		PrintFunctions(0, 2000, "\n4.Regras do Jogo e Avisos");
		PrintFunctions(0, 2000, "\n5.Sair");
		PrintFunctions(0, 2000, "\n//-:");
}

int ReturnToMainMenu(){
	PrintFunctions(5, 0, "");
	loadedOptions = false;
	menupart = 0;
}