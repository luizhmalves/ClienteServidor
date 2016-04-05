#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int randomizaCpuMemoria(){
	
	srand((unsigned)time(NULL));
	return (rand()% 90);
}
