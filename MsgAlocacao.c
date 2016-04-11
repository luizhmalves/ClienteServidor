#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca/sDistribuido.h"

void MsgAlocacao(char *mensagem){
	
	char buf[6];
	int tempo = randomizaTempo();
	char mensagem1[14];
	int indice = 0;
	int indice1 = 0;
	
	for(indice = 0; mensagem[indice] != '\0'; indice ++){
		
		if(mensagem[indice] != '?'){
			
			mensagem1[indice1] = mensagem[indice];
			indice1++;
		}
	}
	for(indice1 = 0; mensagem1[indice1] = '\0'; indice++){
		
		mensagem[indice] = mensagem1[indice1];
	}
	sprintf(buf,"%d",tempo);
	strcat(mensagem, buf);
	strcat(mensagem, "#");
}
