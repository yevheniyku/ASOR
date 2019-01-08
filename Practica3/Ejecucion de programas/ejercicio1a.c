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

  char * command;
  command = (char *) malloc(64 * sizeof(char));

  for(int i = 1; i < argc; i++){
    strcat(command, argv[i]);
    strcat(command, " ");
  }

  system(command);
  printf("El comando terminó de ejecutarse\n");
  free(command);
  
  return 0;
}
