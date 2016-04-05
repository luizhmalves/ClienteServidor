#include <stdio.h>
#include "biblioteca/sDistribuido.h"
void main(int argc, char *argv[]){
	int opcao;
	printf("Este computador eh: <1> Servidor <2> Cliente.\n");
	scanf("%d",&opcao);
	switch(opcao){
		case 1:
			servidor();
		break;
		case 2:
			cliente();
		break;
		default:
			printf("Opcao invalida!!!\n");
	}
}
