#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int randomizaTempo(){
	
	srand((unsigned)time(NULL));
	return 10 + (rand()% 60000);
}
