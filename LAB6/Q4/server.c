#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345

int main(int argc, char *argv[]) {
  int sock, status, buflen;
  struct sockaddr_in addr;
  char buffer[1024];

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

  // send a unicast message
  memset(buffer, 0, sizeof(buffer));
  strncpy(buffer, "Hello, unicast world!", sizeof(buffer));
  buflen = strlen(buffer) + 1;
  status = sendto(sock, buffer, buflen, 0, (struct sockaddr *)&addr, sizeof(addr));
  if (status < 0) {
    perror("error sending unicast message");
    exit(1);
  }

  // send a multicast message
  memset(buffer, 0, sizeof(buffer));
  strncpy(buffer, "Hello, multicast world!", sizeof(buffer));
  buflen = strlen(buffer) + 1;
  addr.sin_addr.s_addr = inet_addr("239.255.255.250"); // set multicast address
  status = sendto(sock, buffer, buflen, 0, (struct sockaddr *)&addr, sizeof(addr));
  if (status < 0) {
    perror("error sending multicast message");
    exit(1);
  }

  // send a broadcast message
  memset(buffer, 0, sizeof(buffer));
  strncpy(buffer, "Hello, broadcast world!", sizeof(buffer));
  buflen = strlen(buffer) + 1;
  addr.sin_addr.s_addr = INADDR_BROADCAST; // set broadcast address
  status = sendto(sock, buffer, buflen, 0, (struct sockaddr *)&addr, sizeof(addr));
  if (status < 0) {
    perror("error sending broadcast message");
    exit(1);
  }

  // close the socket
  close(sock);

  return 0;
}
