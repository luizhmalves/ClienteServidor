#include <stdio.h>
#include <stdlib.h>
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
#include "biblioteca/sDistribuido.h"


#define TRUE 1

void cliente(){
	
	int sockfd;
	struct sockaddr_in local;
	char mensagemVerificacao[12]="#cpu?#mem?#";
	char buffer[20];
	int indice;
	int quantidade;
	int *servidores;
	int porta;
	
	printf("Informe a quantidade de servidores compõe está subrede:\n");
	scanf("%d",&quantidade);
	
	servidores = (int *) malloc(quantidade * sizeof(int));
	if(!servidores){
		perror("Erro na alocação da quantidade de servidores.\n");
		exit(1);
	}
	for(indice = 0; indice < quantidade; indice++){
		printf("Informe o número da porta do servidor %d.\n", indice + 1);
		scanf("%d",&porta);
		servidores[indice] = porta;
	}
	indice = 0;
	while(indice < quantidade){
	
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
			perror("Falha na criação do soquete!\n");
			//sleep(120);
			exit(1);
		}
	
		memset(&local, 0, sizeof(local));
		local.sin_family		= AF_INET;
		local.sin_port			= htons(servidores[indice]);
		//inet_aton(ip[i][j], &(local.sin_addr)); //uso geral
		inet_aton("127.0.0.1", &(local.sin_addr));
	
		if(connect(sockfd, (struct sockaddr *) &local, sizeof(local)) < 0){
			perror("Falha ao conectar!\n");
		}
		printf("Comunicacao com o servidor porta = %d\n", servidores[indice]);
		
		strcpy(buffer, mensagemVerificacao);
		
		if(send(sockfd, buffer, 21, 0) < 0){
			perror("Falha no envio da mensagem de verificação.\n");
		}
		if(recv(sockfd, buffer, 21, 0) < 0){
			perror("Erro no recebimento de resposta da consulta.\n");
		}
		printf("Resposta de consulta ao servidor: %s\n",buffer);
		MsgAlocacao(buffer);
		if(send(sockfd, buffer, 21, 0) < 0){
			perror("Falha no envio da mensagem de alocação.\n");
		}
	
		if(recv(sockfd, buffer, 21, 0) < 0){
			perror("Erro no recebimento de resposta da consulta.\n");
		}
		
		
		printf("Resposta de alocação do servidor: %s\n",buffer);	
		
		
		if(strcmp(buffer,"#concedida#") == 0){
			
				indice ++;
				close(sockfd);
				sleep(10);
					
		}else if(strcmp(buffer,"#negada#") == 0){
			
			indice ++;
			close(sockfd);
			sleep(10);
		
		}
		if(indice == quantidade){
			indice = 0;
		}
		close(sockfd);
		
	}		
}
