#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

void main() {
	// Create client socket
	int clientSocket;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Define server address
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9006);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	//Establish Connection with server
	int connectionStatus = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	if(connectionStatus == -1) {
		printf("Attempt to make connection failed! Aborting!\n");
		exit(1);
	}
	
	char serverMsg[256];
	char clientMsg[256];
	
	int serverSocket;
	recv(clientSocket, &serverMsg, sizeof(serverMsg),0);
	printf("Server : %s\n",serverMsg);
        
	while(1) {
		bzero(&serverMsg, strlen(serverMsg));
                printf("Client > ");
                gets(clientMsg);
                send(clientSocket,&clientMsg,sizeof(clientMsg),0);
		if(strcmp(clientMsg, "exit") == 0) break;
                recv(clientSocket,&serverMsg,sizeof(serverMsg),0);
                printf("\nServer : %s\n",serverMsg);
		if(strcmp(serverMsg, "exit") == 0) break;
        }
	close(clientSocket);
}
