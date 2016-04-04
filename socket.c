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

#define PORT 1234

int main(){


	int fdSocket, mainSocket;
	struct sockaddr_in socketAddr, socketAddr2;
	socklen_t sockLen;

	int x, server;
	char texto[4];

	scanf("%d", &server);

	if(server==1){
		if((mainSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
			perror("Unable to create socket\n");
			printf("Exit %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}

		//Setting socket parameters
		memset(&socketAddr, 0, sizeof(socketAddr));
		socketAddr.sin_family      = AF_INET;
		socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		socketAddr.sin_port        = htons(PORT);
	    
		sockLen = sizeof(socketAddr);

		//Bind between socket and descriptor
		if(bind(mainSocket, (struct sockaddr *)&socketAddr, sockLen) < 0){
			perror("Unable to bind socket\n");
			printf("Exit %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}

		//Waiting for connections. The second parameter is the size of the queue for waiting connections
		if(listen(mainSocket, 100) < 0){
			perror("Unable to listen\n");
			printf("Exit %s:%d\n", __FILE__, __LINE__);
			exit(1);
		}

		memset(&socketAddr2, 0, sizeof(socketAddr2));

		printf("aguardando conexão\n");
		//Accept connection on a socket
		fdSocket = accept(mainSocket, (struct sockaddr *)&socketAddr2, &sockLen);

		printf("conexão aceita\n");

		getchar();
		gets(texto);

		if(send(fdSocket, texto, 4, 0) < 0){
			perror("Unable to send message\n");
		}

		printf("mensagem enviada\n");

		scanf("%d", &x);

		if(send(fdSocket, (char *)&x, sizeof(int), 0) < 0){
			perror("Unable to send message\n");
		}

		printf("outra mensagem enviada\n");
		printf("Ambas mensagens enviadas\n");

		close(mainSocket);
		close(fdSocket);


	}
	else{

	if((fdSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Unable to create socket\n");
		printf("Exit %s:%d\n", __FILE__, __LINE__);
		exit(1);
	}

	//Setting socket parameters
	memset(&socketAddr, 0,sizeof(socketAddr));
     	socketAddr.sin_family = AF_INET;	
     	socketAddr.sin_port   = htons(PORT);
     	inet_aton("localhost", &(socketAddr.sin_addr));	//Set the destination address
     
	printf("vou conectar\n");

	//Connect to a socket
    	if(connect(fdSocket, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) < 0){
		return -1;
	}

	printf("aguardando mensagem\n");

	if(recv(fdSocket, texto, 4, 0) < 0){
		perror("Unable to receive message\n");
	}
	
	printf("%s\n", texto);

	if(recv(fdSocket, (const char *)&x, sizeof(int), 0) < 0){
		perror("Unable to receive message\n");
	}

	printf("%d\n", x);

	}
	return 0;

}

