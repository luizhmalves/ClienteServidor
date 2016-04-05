#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int randomizaMemoria(){
	
	srand((unsigned)time(NULL));
	return (rand()% 90);
}
