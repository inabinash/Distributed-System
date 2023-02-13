// Server side implementation of UDP client-server model
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define MAXLINE 100

// Driver code
int main() {
	int sockfd;
	char buffer[100];
	const char *hello = "Hello from server . I am server .";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd >=0) printf("Socket creation successful\n");

	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = 8000;
	
	// Bind the socket with the server address
	int bindReturn=bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) ;
	if(bindReturn==0) printf("Server socket binded to a server addres successfully\n");
	
    
    int clientAddrlen=sizeof(cliaddr);

    while(1){
        printf("Server waiting for client requests..\n");
        int receivedMsgLength= recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&clientAddrlen);
	    buffer[receivedMsgLength] = '\0';
        
	    sendto(sockfd, (const char *)hello, strlen(hello) ,MSG_CONFIRM, (const struct sockaddr *) &cliaddr,sizeof(cliaddr));
	    
    }
	
	
	return 0;
}
