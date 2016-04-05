#include <stdio.h>
#include <string.h>
#include "biblioteca/sDistribuido.h"

char converteIntString(int opcao){
	char mensagem[14];
	mensagem[0] = '#';
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	char verificacao[9];
	char alocacao[15];
	int tempo = randomizaTempo();
	int memoria = randomizaCpuMemoria();
	int cpu = randomizaCpuMemoria();
	if (opcao == 1){
		sprintf(bufCpu,"%cpu",cpu);
		strcat(mensagem, bufCpu);
		sprintf(bufMem,"%memoria", memoria);
		strcat(mensagem, bufMem);
		return mensagem;
	}else{
		sprintf(bufCpu,"%cpu",cpu);
		strcat(mensagem, bufCpu);
		sprintf(bufMem,"%memoria", memoria);
		strcat(mensagem, bufMem);
		sprintf(bufTempo, "%tempo", tempo);
		strcat(mensagem, bufTempo);
		return mensagem;
	}
	/* FazerDepois problemas no retorno usar ponteiro como argumento
	 *  e passar mensagem depois de cocatenada para o ponteiro
	 */
}
