#include "basicFunctions.h"

int PrintFunctions(int type, int sleepTime, char charToPrint[]){
	switch(type){
		case 0: 			///SO PRINTA
			printf("%s", charToPrint);
		break;
		case 1: 			///PRINTA E SLEEPA
			printf("%s", charToPrint);
			Sleep(sleepTime);
		break;
		case 2: 			///APAGA ANTES E PRINTA E SLEEPA
			system("cls");
			printf("%s", charToPrint);
			Sleep(sleepTime);
		break;
		case 3: 			///PRINTA E SLEEPA E APAGA DPS
			printf("%s", charToPrint);
			Sleep(sleepTime);
			system("cls");
		break;
		case 4: 			///APAGA ANTES E PRINTA E SLEEPA E APAGA DPS
			system("cls");
			printf("%s", charToPrint);
			Sleep(sleepTime);
			system("cls");
		break;
		case 5: 			///APAGA ANTES E NAO PRINTA NADA
			system("cls");
		break;
		case 6: 			///APAGA ANTES E SO PRINTA
			system("cls");
			printf("%s", charToPrint);
		break;
	}
}

int LoadingAnimation(int sleepTime, bool showLoadingText[], int loadingSize, char normalChar[], char specialChar[])
{
	
	if(loadingSize <= 0){
		loadingSize = 12;
	}
	
	char loadingArray[loadingSize];
	
	int x = 0;
	
	for(x; x < loadingSize; x++){
		loadingArray[x] = normalChar[0];
	}
	
	x = 0;
	
	int cont = 0;
	
	for(x; x < loadingSize; x++){
		
		if(showLoadingText){
			printf("/Carregando/");
			printf("\n");	
		}
		
		loadingArray[cont] = specialChar[0];
		
		PrintFunctions(1, sleepTime, loadingArray);
		
		loadingArray[cont] = normalChar[0];
		
		cont++;
		
		system("cls");
	}
}