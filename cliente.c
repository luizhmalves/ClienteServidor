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

#define PORTA 1234
#define TRUE 1

void cliente(){
	
	int sockfd;
	struct sockaddr_in local;
	char mensagemVerificacao[12]="#cpu?#mem?#";
	char buffer[20];
	
	/* FazerDepois colocar apartir daqui em um loop
	 * Criar matriz com os endereços de ip
	 * criar vetor de inteiros das portas para teste local
	*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Falha na criação do soquete!\n");
		exit(1);
	}
	
	memset(&local, 0, sizeof(local));
	local.sin_family		= AF_INET;
	local.sin_port			= htons(PORTA);
	//inet_aton(ip[i][j], &(local.sin_addr)); //uso geral
	inet_aton("127.0.0.1", &(local.sin_addr));
	
	if(connect(sockfd, (struct sockaddr *) &local, sizeof(local)) < 0){
		perror("Falha ao conectar!\n");
	}
	
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
	
	/*if(strncmp(buffer,"#concedida#", 11) == 0){
		MsgAlocacao(copMensagem);
		if(send(sockfd, buffer, 16, 0) < 0){
			perror("Falha no envio da mensagem de alocação.\n");
		}
	}else if(strncmp(buffer,"#negada#", 8)){
		close(sockfd);
		//break quando houver loop.
	}*/		
}
