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
	struct sockaddr_un local;
	char mensagemVerificacao[12]="#cpu?#mem?#";
	char buffer[20];
	int i;
	int j;
	int quantidade;
	char **servidores;
	
	
	printf("Informe a quantidade de servidores compõe está subrede:\n");
	scanf("%d",&quantidade);
	
	servidores = (char *) malloc(quantidade * sizeof(char *));
	if(!servidores){
		perror("Erro na alocação das linhas da matriz de servidores.\n");
		exit(1);
	}
	for(i = 0; i < quantidade; i++){
		servidores[i] = (char *) malloc(100 * sizeof(char *));
		if(!servidores[i]){
			perror("Erro na alocação das linhas da matriz de servidores.\n");
			exit(1);
		}		
	}
	for(i = 0; i < quantidade; i++){
		printf("Informe o nome do servidor %d.\n", i + 1);
		scanf("%s",servidores[i]);
	}
	
	i = 0;
	while(i < quantidade){
	
		if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
			perror("Falha na criação do soquete!\n");
			exit(1);
		}
	
		memset(&local, 0, sizeof(local));
		local.sun_family		= AF_UNIX;
		strcpy(local.sun_path,servidores[i]);
		
	
		if(connect(sockfd, (struct sockaddr *) &local, sizeof(local)) < 0){
			perror("Falha ao conectar!\n");
		}
		printf("Comunicacao com o servidor %s\n", servidores[i]);
		
		//Passagem da requisição de verificação para o buffer
		strcpy(buffer, mensagemVerificacao);
		
		if(send(sockfd, buffer, 21, 0) < 0){
			perror("Falha no envio da mensagem de verificação.\n");
		}
		if(recv(sockfd, buffer, 21, 0) < 0){
			perror("Erro no recebimento de resposta da consulta.\n");
		}
		
		printf("Resposta de consulta ao servidor: %s\n",buffer);
		
		//Criação da mensagem de alocação
		MsgAlocacao(buffer);
		
		if(send(sockfd, buffer, 21, 0) < 0){
			perror("Falha no envio da mensagem de alocação.\n");
		}
	
		if(recv(sockfd, buffer, 21, 0) < 0){
			perror("Erro no recebimento de resposta da consulta.\n");
		}
		
		
		printf("Resposta de alocação do servidor: %s\n",buffer);	
		
		//Lógica para requisições concedidas ou negadas
		if(strcmp(buffer,"#concedida#") == 0){
			
			i++;
			close(sockfd);
			sleep(10);
					
		}else if(strcmp(buffer,"#negada#") == 0){
			
			i++;
			close(sockfd);
			sleep(10);
		
		}
		if(i == quantidade){
			i = 0;
		}
		
		
	}		
}
