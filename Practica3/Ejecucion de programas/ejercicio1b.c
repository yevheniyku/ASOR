#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  if(argc < 2){
    perror("Faltan argumentos");
    return -1;
  }

  execvp(argv[1], argv + 1);
  printf("El comando terminó de ejecutarse\n");

  return 0;
}
