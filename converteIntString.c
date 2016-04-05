#include <stdio.h>
#include <string.h>
#include "main.h"

void *converteIntString(char *retorno[15],int opcao){
	int indice;
	char mensagem[15];
	mensagem[0] = '#';
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	char verificacao[9];
	char alocacao[15];
	int tempo = randomizaTempo();
	int memoria = randomizaMemoria();
	int cpu = randomizaCpu();
	if (opcao == 1){
		sprintf(bufCpu,"%cpu",cpu);
		strcat(mensagem, bufCpu);
		sprintf(bufMem,"%memoria", memoria);
		strcat(mensagem, bufMem);
		for(indice = 0; indice < 15; indice ++){
			*retorno[indice] = mensagem[indice];
		}
		//return (retorno);
		
	}else{
		sprintf(bufCpu,"%cpu",cpu);
		strcat(mensagem, bufCpu);
		sprintf(bufMem,"%memoria", memoria);
		strcat(mensagem, bufMem);
		sprintf(bufTempo, "%tempo", tempo);
		strcat(mensagem, bufTempo);
		for(indice = 0; indice < 15; indice ++){
			*retorno[indice] = mensagem[indice];
		}
		//return (retorno);
	}
	/* FazerDepois problemas saida falha de segmentação
	 * testada separadamente somente com as funções
	 * de randomização necessárias
	 * e um main generico como este
	 * #include "main.h"
int main(){
	
	int opcao = 1;
	char mensagem[15];
	converteIntString(mensagem[15],opcao);
	printf("%s\n", mensagem[15]);
	return 0;
}
	 */
}

