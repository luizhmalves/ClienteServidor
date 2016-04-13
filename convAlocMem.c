#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int convAlocMem(char *mensagem){
	int indice;
	int indice1;
	char buf[2];
	int mem;
	
	for(indice = 0; indice < 6; indice ++){
		if(indice < 3){
			break;
		}
		if (mensagem[indice] != '#'){
			buf[indice1] = mensagem[indice];
			indice1++;
		}
	}
	
	mem = atoi(buf);
	return mem;
}
