#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void convAlocMem(char *mensagem){
	int indice;
	int indice1;
	char buf[2];
	int mem;
	for(indice = 3; indice < 6; indice ++){
		if (mensagem[indice] != '#'){
			buf[indice1] = mensagem[indice];
			indice1++;
		}
	}
	mem = atoi(buf);
	return mem;
}
