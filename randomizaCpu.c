#include <stdio.h>
#include <stdlib.h>
#include "biblioteca/sDistribuido.h"
//Função de randomização de quantidade de cpu

int randomizaCpu(){
	int semente = randomizaMemoria();
	srand(semente);
	return (rand()% 90);
}
