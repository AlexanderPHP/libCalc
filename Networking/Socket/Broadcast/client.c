#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BCAST_IP "192.168.1.255"
#define BCAST_PORT 1234
#define MSG_SIZE 100

int main() {
  int sockfd;
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  char message[MSG_SIZE];
  socklen_t sockaddr_len;

  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sockfd < 0) {
    perror("Socket error");
    exit(1);
  }

  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(BCAST_PORT);
  inet_aton(BCAST_IP, &client_addr.sin_addr);

  sockaddr_len = sizeof(struct sockaddr_in);

  bind(sockfd, (struct sockaddr *) &client_addr, sockaddr_len);

  if (recvfrom(sockfd, &message, MSG_SIZE, 0, (struct sockaddr *) &server_addr, &sockaddr_len) < 0) {
    perror("Error recvfrom");
    exit(1);
  }

  printf("%s(%d): %s\n", inet_ntoa(server_addr.sin_addr), server_addr.sin_port, message);

  close(sockfd);

  return 0;
}
