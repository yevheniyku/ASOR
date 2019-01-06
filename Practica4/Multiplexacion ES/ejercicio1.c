#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int errno;
  fd_set rfds;
  char buff[257];
  char *tub1 = "fifo1";
  char *tub2 = "fifo2";

  int fifo1 = mkfifo(tub1, 0777);

  if(fifo1 == -1){
    perror("ERROR: No se ha podido crear el primer pipe");
    exit(EXIT_FAILURE);
  }

  int fifo2 = mkfifo(tub2, 0777);

  if(fifo2 == -1){
    perror("ERROR: No se ha podido crear el segundo pipe");
    exit(EXIT_FAILURE);
  }

  int pipe1 = open(tub1, O_RDONLY | O_NONBLOCK);
  int pipe2 = open(tub2, O_RDONLY | O_NONBLOCK);

  if(pipe1 == -1){
    perror("ERROR: No se ha podido abrir el primer pipe");
    exit(EXIT_FAILURE);
  }
  else if(pipe2 == -1){
    perror("ERROR: No se ha podido abrir el segundo pipe");
    exit(EXIT_FAILURE);
  }

  int slct, curpipe;

  do {
    int numpipe;
    ssize_t readlen = 256;
    //inicializamos el conjunto
    FD_ZERO(&rfds);
    FD_SET(pipe1, &rfds);
    FD_SET(pipe2, &rfds);

    /*
      1 argumento: el pipe mayor del conjunto
      2 argumento: el conjunto de pipes de lectura
      3 argumento: el conjunto de pipes de escritura (NULL)
      4 argumento: el conjunto de errores? (NULL)
      5 argumento: timeout  (NULL)
    */
    slct = select((pipe1 < pipe2) ? pipe2 + 1 : pipe1 + 1, &rfds, NULL, NULL, NULL);

    if(slct > 0){
      // en que pipe estamos
      if(FD_ISSET(pipe1, &rfds)){
        numpipe = 1;
        curpipe = pipe1;
      }
      else if(FD_ISSET(pipe2, &rfds)){
        numpipe = 2;
        curpipe = pipe2;
      }

      while(readlen == 256){
        readlen = read(curpipe, buff, 256);

        if(readlen == -1){
          perror("No se ha podido leer el pipe");
          exit(EXIT_FAILURE);
        }
        buff[readlen] = '\0';

        printf("Tuberia %i: %s", numpipe, buff);
      }

      if(readlen < 256 && numpipe == 1){
        close(pipe1);
        pipe1 = open(tub1, O_RDONLY | O_NONBLOCK);
      }
      else if(readlen < 256 && numpipe == 2){
        close(pipe2);
        pipe2 = open(tub2, O_RDONLY | O_NONBLOCK);
      }
    }
  } while(slct != -1);

  close(pipe1);
  close(pipe2);

  return 0;
}
