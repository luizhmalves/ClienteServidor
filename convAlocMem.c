#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Função de conversão de string para inteiro capacidade de mem
int convAlocMem(char *mensagem){
	
	int indice = 0;
	int indice1 = 0;
	char buf[2];
	int mem;
	
	for(indice = 0; indice < 10; indice ++){
		if(indice > 5){
			if (mensagem[indice] != '#'){
				if (mensagem[indice] != 'm'){
					if (mensagem[indice] != 'e'){
						if(mensagem[indice] != 'u'){
							buf[indice1] = mensagem[indice];
							indice1++;
						}
					}
				}
			}
		}
	}
	
	mem = atoi(buf);
	return mem;
}
