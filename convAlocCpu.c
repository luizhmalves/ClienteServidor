#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convAlocCpu(char *mensagem){
	
	char bufCpu[2];
	int cpu,indice;
	int indice1 = 0;
	for(indice = 0; indice < 3; indice++){
		
		if(mensagem[indice] != '#'){
			bufCpu[indice1] = mensagem[indice];
			indice1++;
		}
	}
	cpu = atoi(bufCpu);
	return cpu;	
}
