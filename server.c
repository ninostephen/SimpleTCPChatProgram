#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

void main() {
	//server message 
	char serverMsg[256] = "You have successfully connected\n";
	char clientMsg[256];
  
	//create server socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	//define server address and port
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9006);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	//Bind to port
	int bindStatus = bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(bindStatus == -1) {
		printf("Failed to bind to port!\n");
		exit(1);
	}
	printf("Server binded to port 9002\n");
	listen(serverSocket,5);
	
        // Create client socket
        int clientSocket;
	clientSocket = accept(serverSocket, NULL, NULL);
        // Send the status message to client
	send(clientSocket,serverMsg,sizeof(serverMsg),0);
	while(1) {
		bzero(&clientMsg, strlen(clientMsg));
                recv(clientSocket,&clientMsg,sizeof(clientMsg),0);
                printf("\nClient : %s\n",clientMsg);
                if(strcmp(clientMsg, "exit") == 0) break;
                printf("Server > ");
                gets(serverMsg);
                send(clientSocket,&serverMsg,sizeof(serverMsg),0);
                if(strcmp(serverMsg, "exit") == 0) break;
	}
	
	//close scoket
	close(serverSocket);
}
