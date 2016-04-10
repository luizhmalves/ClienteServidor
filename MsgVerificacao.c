#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca/sDistribuido.h"

void MsgVerificacao(char *mensagem){
	
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	char verificacao[9];
	char alocacao[14];
	int memoria = randomizaMemoria();
	int cpu = randomizaCpu();
	
	strcat(mensagem, "#");
	sprintf(bufCpu,"%d",cpu);
	strcat(mensagem, bufCpu);
	strcat(mensagem, "?#");	
	sprintf(bufMem,"%d", memoria);
	strcat(mensagem, bufMem);
	strcat(mensagem, "?#");
}


