#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
  if(argc != 3){
    printf("USAGE: %s <ip> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct addrinfo hints;
  struct addrinfo *res;
  int udp_socket;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags    = AI_PASSIVE;

  int r = getaddrinfo(argv[1], argv[2], &hints, &res);

  if(r != 0){
    perror("No se ha podido hacer la consulta getaddrinfo");
    exit(EXIT_FAILURE);
  }

  udp_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  bind(udp_socket, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);

  struct sockaddr_storage client;
  socklen_t clientlen = sizeof(client);
  char buf[2];
  char host[NI_MAXHOST], serv[NI_MAXSERV];
  ssize_t c;
  int fd = -1;
  fd_set fdset;

  while(1){
    while(r == -1){
      FD_ZERO(&fdset);
      FD_SET(udp_socket, &fdset);
      FD_SET(0, &fdset);
      fd = select(udp_socket+1, &fdset, NULL, NULL, NULL);
    }

    time_t t = time(NULL);
    struct tm *local;
    local = localtime(&t);

    if(FD_ISSET(udp_socket, &fdset)){

      c = recvfrom(udp_socket, &buf, sizeof(buf), 0, (struct sockaddr*) &client, &clientlen);
      getnameinfo((struct sockaddr*) &client, clientlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
      printf("[NET] Recieved message from %s:%s\n", host, serv);

      if(buf[0] == 't') {
        char msg[8];

        strftime(msg, 18, "%R", local);
        sendto(udp_socket, &msg, sizeof(msg), 0, (struct sockaddr*) &client, clientlen);
      }
      else if(buf[0] == 'd'){
        char msg[10];

        strftime(msg, 256, "%d/%m/%y", local);
        sendto(udp_socket, &msg, sizeof(msg), 0, (struct sockaddr*) &client, clientlen);
      }
      else{
        printf("Usage send <d> for date or <t> for time\n");
      }
    }
    else{
      char command[2];
      char msg[50];
      read(0, command, 2);

      printf("Recieved message from console\n");
      command[1] = '\0';

      if(command[0] == 't'){
        size_t time_bytes = strftime(msg, 50, "%R", local);
        msg[time_bytes] = '\0';
        printf("Time: %s\n", msg);
      }
      else if(command[0] == 'd'){
        size_t time_bytes =   strftime(msg, 50, "%d/%m/%y", local);
        msg[time_bytes] = '\0';
        printf("Date: %s\n", msg);
      }
      else{
        printf("Usage send <d> for date or <t> for time\n");
      }
    }
  }

  close(udp_socket);

  return 0;
}
