#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convAlocTempo(char *mensagem){
	
	char buf[6];
	int tempo,indice;
	int indice1 = 0;
	for(indice = 6; mensagem[indice] != '\0'; indice++){
		
		if(mensagem[indice] != '#'){
			buf[indice1] = mensagem[indice];
			indice1++;
		}
	}
	tempo = atoi(buf);
	return tempo;	
}
