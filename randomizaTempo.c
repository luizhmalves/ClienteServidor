#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int randomizaTempo(){
	//não testada
	srand((unsigned)time(NULL));
	return 10 + (rand()% 120000);
}
