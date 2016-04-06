#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

void converteIntString(char *mensagem,int n,int opcao){
	int indice;
	strcat(mensagem, "#");
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	char verificacao[9];
	char alocacao[15];
	int tempo = randomizaTempo();
	int memoria = randomizaMemoria();
	int cpu = randomizaCpu();
	if (opcao == 1){
		//mensagem de verificação
		sprintf(bufCpu,"%d",cpu);
		strcat(mensagem, bufCpu);
		strcat(mensagem, "?#");	
		sprintf(bufMem,"%d", memoria);
		strcat(mensagem, bufMem);
		strcat(mensagem, "?#");
		
		
	}else{
		//mensagem de alocação
		sprintf(bufCpu,"%d",cpu);
		strcat(mensagem, bufCpu);
		strcat(mensagem, "?#");	
		sprintf(bufMem,"%d", memoria);
		strcat(mensagem, bufMem);
		strcat(mensagem, "?#");
		sprintf(bufTempo, "%d", tempo);
		strcat(mensagem, bufTempo);
		strcat(mensagem, "#");
		
		
	}
}


