#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função de criação da requisição de quantidade de cpu e mem do servidor
void respostaConsulta(char *mensagem, int cpu, int mem){
	char bufCpu[2];
	char bufMem[2];
		
	strcpy(mensagem, "#");
	sprintf(bufCpu, "%.2d", cpu);
	strcat(mensagem, bufCpu);
	strcat(mensagem, "cpu#");
	sprintf(bufMem, "%.2d", mem);
	strcat(mensagem, bufMem);
	strcat(mensagem, "mem#");
}
