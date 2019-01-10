#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s;

  if(argc != 2){
    printf("Usage: %s <host>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = 0;
  hints.ai_protocol = 0;
  hints.ai_flags    = AI_PASSIVE;

  s = getaddrinfo(argv[1], NULL ,&hints, &result);

  if(s != 0){
    perror("getaddrinfo no ha tenido exito");
    exit(EXIT_FAILURE);
  }

  for(rp = result; rp != NULL; rp = rp->ai_next){
    char buf[NI_MAXHOST];
    if(getnameinfo(rp->ai_addr, rp->ai_addrlen, buf, sizeof(buf), NULL, 0, NI_NUMERICHOST) == 0){
      printf("Host: %s\n", buf);
      printf("Family: %i\n", rp->ai_family);
      printf("Socket Type: %i\n", rp->ai_socktype);
    }
  }

  freeaddrinfo(result);

  return 0;
}
