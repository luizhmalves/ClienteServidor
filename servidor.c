#include <stdio.h>
#include "biblioteca/sDistribuido.h"
#define TRUE 1
void servidor(){
	int cpMem = 90;
	int cpCpu = 90;
	int porta;
	char respostaPositiva[] = "#concedida";
	char respostaNegativa[] = "#negada#";
	//FazerDepois criar função que converta a resposta da consulta em inteiros para enviar ao cliente
	printf("Informe a porta deste servidor:\n");
	scanf("%d",&porta);
	/*
	 * FazerDepois abrir socket para conexão.
	 * Função que converta solicitação cliente em inteiro.
	 * Passar conversão para calculaCPUDisponivel.c
	 * Passar para calculaMemDisponivel.c		
	*/
	
}
