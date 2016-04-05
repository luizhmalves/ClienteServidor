#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *calculaTempo(void *requisicao){
	
	pthread_exit(NULL);

}


int mantemRequisicao(int tempo,int cpRequisicao){
	int t = tempo;
	int cpReq = cpRequisicao;
	pthread_t threads; //handlers das threads
	
		//(handler, atributos, função a ser executada, parâmetro da função)
		pthread_create(&threads,NULL,&calculaTempo,(void *)cpReq);
	
	sleep(t);
	//Deve ser chamada para sincronizar as threads no final
	pthread_join(threads,NULL);
	return cpReq;
}

