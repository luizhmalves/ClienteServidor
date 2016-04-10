#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca/sDistribuido.h"

void MsgVerificacao(char *mensagem,int opcao){
	
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	char verificacao[9];
	char alocacao[14];
	
	
	strcat(mensagem, "#");
	if (opcao == 1){
		int memoria = randomizaMemoria();
		int cpu = randomizaCpu();
		//mensagem de verificação
		sprintf(bufCpu,"%d",cpu);
		strcat(mensagem, bufCpu);
		strcat(mensagem, "?#");	
		sprintf(bufMem,"%d", memoria);
		strcat(mensagem, bufMem);
		strcat(mensagem, "?#");
		
		
	}else{
		int tempo = randomizaTempo();
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


