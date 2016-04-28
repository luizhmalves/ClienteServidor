#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Função de conversão de string para inteiro capacidade de tempo
int convAlocTempo(char *mensagem){
	
	char buf[7];
	int tempo,indice;
	int indice1 = 0;
	
	for(indice = 9; mensagem[indice] != '\0'; indice++){
		if(indice < 9){
			break;
		}else{
			if(mensagem[indice] != '#'){
				if (mensagem[indice] != 'm'){
					if (mensagem[indice] != 'e'){
						buf[indice1] = mensagem[indice];
						indice1++;
					}
				}
			}
		}
	}
	tempo = atoi(buf);
	return tempo;	
}

