#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca/sDistribuido.h"

void MsgVerificacao(char *mensagem){
	
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	int memoria = randomizaMemoria();
	int cpu = randomizaCpu();
		
	strcpy(mensagem, "#");
	sprintf(bufCpu,"%.2d",cpu);
	strcat(mensagem, bufCpu);
	strcat(mensagem, "?#");	
	sprintf(bufMem,"%.2d", memoria);
	strcat(mensagem, bufMem);
	strcat(mensagem, "?#");
}


