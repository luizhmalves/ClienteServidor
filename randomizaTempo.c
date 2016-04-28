#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função de randomização de quantidade de tempo
int randomizaTempo(){
	
	srand((unsigned)time(NULL));
	return 10 + (rand()% 120000);
}
