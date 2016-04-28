#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca/sDistribuido.h"


//Função de conversão de inteiros para string para criar mensagem de alocação
void MsgAlocacao(char *mensagem){
	
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	int memoria = randomizaMemoria();
	int cpu = randomizaCpu();
	int tempo = randomizaTempo();
	
	
	strcpy(mensagem, "#");
	sprintf(bufCpu,"%.2d",cpu);
	strcat(mensagem, bufCpu);
	strcat(mensagem, "cpu#");	
	sprintf(bufMem,"%.2d", memoria);
	strcat(mensagem, bufMem);
	strcat(mensagem, "mem#");
	sprintf(bufTempo,"%.6d",tempo);
	strcat(mensagem, bufTempo);
	strcat(mensagem, "#");
}


	
		
	
