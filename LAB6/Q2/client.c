#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 100

int main(){
    int sockfd;
	char buffer[100];
	const char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd >=0) printf("Socket creation successful\n");

    servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = 8000;
    
    sendto(sockfd, hello, strlen(hello),MSG_CONFIRM, &servaddr, sizeof(servaddr));
    int len=sizeof(servaddr);
    int receivedMsgLength=recvfrom(sockfd,buffer, MAXLINE,MSG_WAITALL, &servaddr,&len);
    buffer[receivedMsgLength]='\0';
    printf("The received msg from server %s\n",buffer);

    close(sockfd);
    return 0;
}
