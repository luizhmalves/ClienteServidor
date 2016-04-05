#include <stdio.h>
#include "biblioteca/sDistribuido.h"
#define TRUE 1
typedef dadosServidor{
	int porta;
	char ip[];//FazerDepois tamanho do vetor
}server
void cliente(){
	int quantServidores;
	int indice;
	int tempo;
	int memoria;
	int cpu;
	server servidores[];
	printf("Informe a quantidade de servidores que estão conectados nessa rede:\n");
	scanf("%d",&quantServidores);
	//FazerDepois a alocação que está faltando ainda
	for(indice = 0; indice < quantServidores; indice ++){
		printf("Informe a porta do servidor %d:\n",(indice + 1));
		scanf("%d",&servidores[indice].porta);
		printf("Informe o IP do servidor %d:\n", (indice +1));
		scanf("%s",&servidores[indice]->ip);//FazerDepois verificação desse acesso ao vetor como ponteiro
	}
	/*
	 * FazerDepois conversão da mensagem de verificação de inteiro para string
	 * converter mensagem de alocação
	 * Enviar para o servidor mensagem de verificação
	 * Aguardar resposta
	 * Se confirmada enviar mensagem de alocação
	 * se negada enviar para outro servidor a mensagem de verificação
	 */
	 while(TRUE){
		tempo = randomizaTempo();
		cpu = randomizaCpuMemoria();
		memoria = randomizaCpuMemoria();
		//FazerDepois retirar as atribuições acima
}
