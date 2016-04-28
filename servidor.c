#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

//Declaração das variáveis globais
int cpu;
int mem;
int reqCpu;
int reqMem;
pthread_mutex_t mutex;

//Thread para atualização de quantidade de cpu e mem do servidor
void* atualizaServidor(void* arg){
	
	int tempo = *(int*) arg;
	int cpCpu,cpMem;
	
	
	cpCpu = reqCpu;
	cpMem = reqMem;
	
	sleep((tempo/1000));
	
	//Semáforo para incremento das variáveis globais
	pthread_mutex_lock(&mutex);
	cpu += cpCpu;
	mem += cpMem;
	
	pthread_mutex_unlock(&mutex);
	pthread_exit((void*) 0);
	
}
//Thread para recebimento e resposta de requisições do cliente
void* servidorThread(void* arg){

	pthread_t thread1;
	char respostaPositiva[12] = "#concedida#";
	char respostaNegativa[9] = "#negada#";
	char buffer_do_cliente[16];	
	int sockEntrada = *(int *) arg;
		
	int reqTempo;
	
	
	
	
	while(TRUE){
		//Receive para recebimento das requisições
		if(recv(sockEntrada,buffer_do_cliente, 21, 0) < 0){
			perror("Falha no recebimento da verificação.\n");
			close(sockEntrada);
			pthread_exit((void*) 0);
		}else{
			//Lógica para verificar se o cliente requisitou verificação
			if(strlen(buffer_do_cliente) == 11){
				
				printf("Pedido de Verificação do Cliente: %s\n", buffer_do_cliente);
				
				//Criação da mensagem de resposta de quantidade de recursos		
				respostaConsulta(buffer_do_cliente,cpu,mem);
				
				// Envio da mensagem de requisição/Consulta	
				if(send(sockEntrada,buffer_do_cliente, 21, 0) < 0){
					perror("Falha no envio da resposta da alocação.\n");
					close(sockEntrada);
					pthread_exit((void*) 0);
				}
					

			}else{
				//Lógica para verificar se o cliente requisitou alocação
				if((strlen(buffer_do_cliente) >= 13) && (strlen(buffer_do_cliente) <= 20)){
					printf("Pedido de Alocação do Cliente: %s\n", buffer_do_cliente);
					
					//Conversão da requisição de alocação para inteiro
					reqCpu = convAlocCpu(buffer_do_cliente);
					reqMem = convAlocMem(buffer_do_cliente);
					reqTempo = convAlocTempo(buffer_do_cliente);
					
					//Lógica para avaliar recursos disponíveis			
					if(((cpu - reqCpu) > 0) && ((mem - reqMem) > 0)){
						
						//Passagem para o buffer a resposta positiva
						strcpy(buffer_do_cliente,respostaPositiva);
						
						if(send(sockEntrada,buffer_do_cliente, 21, 0) < 0){
							perror("Falha no envio da resposta da alocação confirmada.\n");
							close(sockEntrada);
							pthread_exit((void*) 0);
						}
						//Semáforo para decrementação das variáveis globais
						pthread_mutex_lock(&mutex);
						cpu -= reqCpu;
						mem -= reqMem;	
						pthread_mutex_unlock(&mutex);
						
						//Criação da thread para cálculo das variáveis globais
						if(pthread_create(&thread1, NULL, &atualizaServidor, &reqTempo) != 0){
							perror("Erro na criação da thread.\n");
							exit(1);
						}
						
						pthread_detach(thread1);							
										
					}else{
						//Passagem para o buffer a resposta negativa
						strcpy(buffer_do_cliente,respostaNegativa);
						if(send(sockEntrada,buffer_do_cliente, 21, 0) < 0){
							perror("Falha no envio da resposta da alocação negada.\n");
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
	char nome[100];
	struct sockaddr_un local;
	socklen_t sockLen;
	
	pthread_mutex_init(&mutex, NULL);
	printf("Informe o nome deste servidor:\n");
	scanf("%s",nome);
	printf("%s\n",nome);
	
	
	cpu = 90;
	mem = 90;
	
	
	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
		
		perror("Falha na criação do socket.\n");
		exit(1);
	}
	
	//Parâmetros do soquete
	memset(&local, 0, sizeof(local));
	local.sun_family		= AF_UNIX;
	strcpy(local.sun_path,nome);
	sockLen = sizeof(local);
	
	if(bind(sockfd,(struct sockaddr *)&local, sockLen) < 0){
		perror("Falha na ligação do bind.\n");
		exit(1);	
	}
	
	if(listen(sockfd, MAX_VALOR) < 0){
		perror("Falha na escuta da conexão.\n");
		exit(1);
	}
	printf("Aguardando Conexão.\n");
	while(TRUE){
		int cliente;
		struct sockaddr_un remoto;
		int clntLen;
		clntLen = sizeof(remoto);
		pthread_t thread;
		
		
		
		
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
	

}
