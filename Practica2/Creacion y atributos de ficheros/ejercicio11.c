#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/sysmacros.h>
//error
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  struct stat sb;

  if (argc != 2) {
   fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
   exit(EXIT_FAILURE);
  }

  // obtenemos la información
  if (stat(argv[1], &sb) == -1) {
   perror("stat");
   exit(EXIT_FAILURE);
  }

  char * hard = malloc(sizeof(char) * (5 + strlen(argv[1])));
  char * sym  = malloc(sizeof(char) * (5 + strlen(argv[1])));

  strcpy(hard, argv[1]);
  strcpy(sym,  argv[1]);

  if (S_ISREG(sb.st_mode)){
    if(symlink(argv[1], strcat(sym, ".sym")) == -1){
      perror("Fallo al crear enlace simbolico");
      exit(EXIT_FAILURE);
    }
    if(link(argv[1], strcat(hard, ".hard")) == -1){
      perror("Fallo al crear enlace rigido");
      exit(EXIT_FAILURE);
    }
    printf("Los enlaces se han creado correctamente\n");
  }
  else{
    perror("El fichero no ordinario");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
