#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "biblioteca/sDistribuido.h"

#define TRUE 1
#define MAX_VALOR 2147483647


int cpu;
int mem;
int reqCpu;
int reqMem;
pthread_mutex_t mutex;


void* atualizaServidor(void* arg){
	int tempo = *(int*) arg;
	
	
	pthread_mutex_lock(&mutex);
	cpu -= reqCpu;
	mem -= reqMem;
	pthread_mutex_unlock(&mutex);
	sleep(tempo);
	cpu += reqCpu;
	mem += reqMem;
	
}
void* servidorThread(void* arg){

	pthread_t thread1;
	char respostaPositiva[12] = "#concedida#";
	char respostaNegativa[9] = "#negada#";
	char buffer_do_cliente[16];	
	int sockEntrada = *(int *) arg;
	
	
	
	int reqTempo;
	
	
	
	
	while(TRUE){
		
		if(recv(sockEntrada,buffer_do_cliente, 21, 0) < 0){
			perror("Falha no recebimento da verificação.\n");
			close(sockEntrada);
			pthread_exit((void*) 0);
		}else{
			
			
			if(strlen(buffer_do_cliente) == 11){
			
				printf("Pedido de Verificação do Cliente: %s\n", buffer_do_cliente);
				pthread_mutex_lock(&mutex);				
				respostaConsulta(buffer_do_cliente,cpu,mem);
				pthread_mutex_unlock(&mutex);	
				if(send(sockEntrada,buffer_do_cliente, 21, 0) < 0){
					perror("Falha no envio da resposta da alocação.\n");
					close(sockEntrada);
					pthread_exit((void*) 0);
				}
					

			}else{
				
				if((strlen(buffer_do_cliente) >= 13) && (strlen(buffer_do_cliente) <= 20)){
					printf("Pedido de Alocação do Cliente: %s\n", buffer_do_cliente);
					
					reqCpu = convAlocCpu(buffer_do_cliente);
					reqMem = convAlocMem(buffer_do_cliente);
					reqTempo = convAlocTempo(buffer_do_cliente);
								
					if((cpu - reqCpu) > 0){
						if ((mem - reqMem) > 0){
							strcpy(buffer_do_cliente,respostaPositiva);
							if(send(sockEntrada,buffer_do_cliente, 21, 0) < 0){
								perror("Falha no envio da resposta da alocação.\n");
								close(sockEntrada);
								pthread_exit((void*) 0);
							}
							
							if(pthread_create(&thread1, NULL, &atualizaServidor, &reqTempo) != 0){
								perror("Erro na criação da thread.\n");
								exit(1);
							}
		
							pthread_detach(thread1);							
						}				
					}else{
						
						strcpy(buffer_do_cliente,respostaNegativa);
						if(send(sockEntrada,buffer_do_cliente, 21, 0) < 0){
							perror("Falha no envio da resposta da alocação.\n");
							close(sockEntrada);
							pthread_exit((void*) 0);
						}
						
					}
					
					
					close(sockEntrada);
					pthread_exit((void*) 0);
										
				}
			}
		}
		
	}	
}

void servidor(){
			
	int sockfd;
	int porta;
	struct sockaddr_in local;
	socklen_t sockLen;
	
	
	printf("Informe a porta local para este servidor:\n");
	scanf("%d",&porta);
	pthread_mutex_init(&mutex, NULL);
	
	cpu = 90;
	mem = 90;
	
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		
		perror("Falha na criação do socket.\n");
		exit(1);
	}
	
	memset(&local, 0, sizeof(local));
	local.sin_family		= AF_INET;
	local.sin_addr.s_addr	= htonl(INADDR_ANY);
	local.sin_port			= htons(porta);
	sockLen = sizeof(local);
	
	if(bind(sockfd,(struct sockaddr *)&local, sockLen) < 0){
		perror("Falha na ligação do bind.\n");
		exit(1);	
	}
	
	if(listen(sockfd, MAX_VALOR) < 0){
		perror("Falha na escuta da conexão.\n");
		exit(1);
	}
	pthread_mutex_init(&mutex, NULL);
	while(TRUE){
		int cliente;
		struct sockaddr_in remoto;
		int clntLen;
		clntLen = sizeof(remoto);
		pthread_t thread;
		
		
		printf("Aguardando Conexão.\n");
		memset(&remoto, 0, sizeof(remoto));
		if((cliente = accept(sockfd, (struct sockaddr *)&remoto, &clntLen)) < 0){
			perror("Erro no accept");
			exit(1);
		}
		
		if(pthread_create(&thread, NULL, &servidorThread, &cliente) != 0){
			perror("Erro na criação da thread.\n");
			exit(1);
		}
		
		pthread_detach(thread);
	}
	pthread_mutex_destroy(&mutex);

}
