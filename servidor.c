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
#include "biblioteca/sDistribuido.h"
#define TRUE 1
#define TAMANHO 16
#define PORTA 1234

void* servidorThread(void* arg){
	char respostaPositiva[12] = "#concedida#";
	char respostaNegativa[9] = "#negada#";
	char buffer_do_cliente[16];
	
	int sockEntrada = *(int *) arg;
	int cpu = atualizaCpu(90,0,1);
	int mem = atualizaMem(90,0,1);
	int reqCpu;
	int reqMem;
	int reqtempo;
		
	
	while(TRUE){
		if(recv(sockEntrada,buffer_do_cliente, 16, 0) < 0){
			perror("Falha no recebimento da verificação.\n");
			close(sockEntrada);
			pthread_exit((void*) 0);
		}else{
			
			
			if(strlen(buffer_do_cliente) == 9){
			
				printf("Pedido de Verificação do Cliente: %s.\n", buffer_do_cliente);
				
				respostaConsulta(buffer_do_cliente,cpu,mem);//Duvida envio a resposta de consulta primeiro 
				if(send(sockEntrada,buffer_do_cliente, 16, 0) < 0){
					perror("Falha no envio da resposta da alocação.\n");
					close(sockEntrada);
					pthread_exit((void*) 0);
				}		

			}else{
				
				if(strlen(buffer_do_cliente) == 14){
					printf("Pedido de Alocação do Cliente: %s.\n", buffer_do_cliente);
					/*FAZERDEPOIS até aqui está certo
					* retorno da resposta positiva e negada está errado
					*/
					reqCpu = convAlocCpu(buffer_do_cliente);
					reqMem = convAlocMem(buffer_do_cliente);
					reqtempo = convAlocTempo(buffer_do_cliente);
					if((cpu - reqCpu) > 0){
						if ((mem - reqMem) > 0){
							strcpy(buffer_do_cliente,respostaPositiva);
							if(send(sockEntrada,buffer_do_cliente, 16, 0) < 0){
								perror("Falha no envio da resposta da alocação.\n");
								close(sockEntrada);
								pthread_exit((void*) 0);/*se concedida fechar thread
								*e ficar atualizando a capacidade da cpu e mem
								*/
							}
						}				
					}else{
						strcpy(buffer_do_cliente,respostaNegativa);
						if(send(sockEntrada,buffer_do_cliente, 16, 0) < 0){
							perror("Falha no envio da resposta da alocação.\n");
							close(sockEntrada);
							pthread_exit((void*) 0);
						}		
						close(sockEntrada);
						pthread_exit((void*) 0);
					}					
				}
			}
		}
		//FazerDepois alocação
		//Recebe alocação
		/*
		sleep(reqtempo);
		cpu = atualizaCpu(cpu,reqCpu,2);
		mem = atualizaMem(mem,reqMem,2);
	}*/
	}	
}
void servidor(){
	
	int sockfd;
	struct sockaddr_in local;
	socklen_t sockLen;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		
		perror("Falha na criação do socket.\n");
		exit(1);
	}
	
	memset(&local, 0, sizeof(local));
	local.sin_family		= AF_INET;
	local.sin_addr.s_addr	= htonl(INADDR_ANY);
	//local.sin_addr.s_addr	= inet_addr("localhost");
	local.sin_port			= htons(PORTA);
	sockLen = sizeof(local);
	
	if(bind(sockfd,(struct sockaddr *)&local, sockLen) < 0){
		perror("Falha na ligação do bind.\n");
		exit(1);	
	}
	
	/*Escuta até 10 clientes*/
	
	if(listen(sockfd, 10) < 0){
		perror("Falha na escuta da conexão.\n");
		exit(1);
	}
	
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

}

