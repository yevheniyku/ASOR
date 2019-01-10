#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
  if(argc != 3){
    printf("USAGE: %s <direccion> <puerto>\n", argv[0]);
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
  int c;

  c = recvfrom(udp_socket, &buf, sizeof(buf), 0, (struct sockaddr*) &client, &clientlen);

  getnameinfo((struct sockaddr*) &client, clientlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

  while(buf[0] != 'q'){
    time_t t = time(NULL);
    struct tm *local;
    local = localtime(&t);

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

    c = recvfrom(udp_socket, &buf, sizeof(buf), 0, (struct sockaddr*) &client, &clientlen);
    getnameinfo((struct sockaddr*) &client, clientlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
  }

  close(udp_socket);

  return 0;
}
