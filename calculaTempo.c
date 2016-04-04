#include<stdio.h>
#include<pthread.h>

//Deve ser declarado como ponteiro para função
int *calculaTempo(void *tempo, void *requisicao){
	
	int t = (int)tempo;
	int req = (int)requisicao;
	sleep(t);
	return req;
	pthread_exit(NULL);

}


int calculaTempo(int t, int cpRequisicao){
	int tempo = t;
	int cpReq = cpRequisicao;
	pthread_t threads; //handlers das threads
	
		//(handler, atributos, função a ser executada, parâmetro da função)
		pthread_create(&threads,int,&calculaTempo,((void *)tempo, (void *)cpReq);
	

	//Deve ser chamada para sincronizar as threads no final
	pthread_join(threads,int);
	

}

