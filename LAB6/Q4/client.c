#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
  int sock, status;
  struct sockaddr_in addr;
  char buffer[BUFSIZE];

  // create a UDP socket
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("error opening socket");
    exit(1);
  }

  // set up address information
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  // bind the socket to the address
  status = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
  if (status < 0) {
    perror("error binding socket");
    exit(1);
  }

  while (1) {
    // wait for incoming packets
    memset(buffer, 0, sizeof(buffer));
    status = recvfrom(sock, buffer, BUFSIZE, 0, NULL, NULL);
    if (status < 0) {
      perror("error receiving message");
      exit(1);
    }

    // print the received message
    printf("Received message: %s\n", buffer);
  }

  // close the socket (this code is never reached)
  close(sock);

  return 0;
}
