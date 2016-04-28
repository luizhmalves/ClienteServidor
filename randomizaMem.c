#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função de randomização de quantidade de memória
int randomizaMemoria(){
	
	srand((unsigned)time(NULL));
	return (rand()% 90);
}
