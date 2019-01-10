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
  if(argc != 4){
    printf("USAGE: %s <direccion> <puerto> <comando> \n", argv[0]);
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

  int c;

  c = sendto(udp_socket, argv[3], sizeof(argv[3])+1, 0, res->ai_addr, res->ai_addrlen);

  printf("Se ha enviado el mensaje correctamente\n");

  char buf[256];
  ssize_t response = recvfrom(udp_socket, buf, 255, 0, res->ai_addr, &res->ai_addrlen);
  buf[response] = '\0';

  printf("Mensaje respuesta: %s\n", buf);

  freeaddrinfo(res);
  close(udp_socket);

  return 0;
}
