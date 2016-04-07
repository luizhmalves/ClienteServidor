#include <stdio.h>
#include <string.h>
#include "biblioteca/sDistribuido.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void converteStringInt(char *mensagem, int tamanho){
	
	char bufCpu[2];
	char bufMem[2];
	char bufTempo[6];
	int cpu,mem,tempo,indice;
	int indice1 = 0;
	int indice2= 0;
	int indice3 = 0;
	for(indice = 0; indice < tamanho; i++){
		if((mensagem[i] != '#' || mensagem != '?') && i < 3){
			bufCpu[indice1] = mensagem[i];
			indice1++;
		}else if ((mensagem[i] != '#' || mensagem[i] != '?') && (i > 3 && i < 8)){
			bufMem[indice2] = mensagem[i];
			indice2++;
		}else if ((mensagem[i] != '#' || mensagem[i] != '?') && (i > 8 && i < tamanho)){
			bufTempo[indice3] = mensagem[i];
			indice3++;
		}
	}
	cpu = atoi(bufCpu);
	mem = atoi(bufMem);
	tempo = atoi(bufTempo);
}
		
	
/*FazerDepois 
 * usar a função atoi();
 * tem que separar a string para converter
 * e enviar como parametro para cada função que calcula
 * testar separadamente
 * necessário criar lógica
 */
}
