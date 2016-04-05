#include <stdio.h>
#include <stdlib.h>
#include "biblioteca/sDistribuido.h"
int randomizaCpu(){
	int semente = randomizaMemoria();
	srand(semente);
	return (rand()% 90);
}
