#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void respostaConsulta(char *mensagem, int cpu, int mem){
	int indice;	
	char bufCpu[2];
	char bufMem[2];
	mensagem =" ";
	
	strcat(mensagem, "#");
	sprintf(bufCpu, "%d", cpu);
	strcat(mensagem, bufCpu);
	strcat(mensagem, "#");
	sprintf(bufMem, "%d", mem);
	strcat(mensagem, bufMem);
	strcat(mensagem, "#");
}
