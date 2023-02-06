// Client code in C to sort the array
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Driver code
int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in server;
	int server_reply[10];int number[10];
    int a;
    printf("Enter the 10 integers of the array ");
    for(int i=0;i<10;i++){
        scanf("%d",&a);
        number[i]=a;
    }
	

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8880);

	// Connect to remote server
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");

	if (send(sock, &number, 10 * sizeof(int), 0) < 0) {
		puts("Send failed");
		return 1;
	}

	// Receive a reply from the server
	if (recv(sock, &server_reply, 10 * sizeof(int), 0) < 0) {
		puts("recv failed");
		return 0;
	}

	puts("Server reply :\n");
	printf("Sum of the elements in the array : %d",server_reply[9]);

	// close the socket
	close(sock);
	return 0;
}
