#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/file.h>
#include <error.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int errno;

  if (argc != 2) {
   fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
   exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

  if(fd == -1){
    printf("Error %ui: %s", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  struct flock lock;
  //miramos el cerrojo sobre el fichero
  int filelock = fcntl(fd, F_GETLK, &lock);

  if(filelock != -1){
    //si esta desbloqueado
    if(lock.l_type == F_UNLCK){
      //creamos un cerrojo para bloquearlo
      lock.l_type = F_WRLCK;
      lock.l_whence = SEEK_SET;
      lock.l_start = 0;
      lock.l_len = 0;
      lock.l_pid = getpid();
      //creamos el cerrojo
      if(fcntl(fd, F_SETLK, &lock) != -1){
        printf("Cerrojo creado\n");
        //mostramos y escribimos el tiempo
        time_t t = time(NULL);
        char time[256];
        struct tm *lt = localtime(&t);
        //para dar formato de hora al time y poder escribirlo
        sprintf(time, "Hora: %d:%d:%d\n", lt->tm_hour, lt->tm_min, lt->tm_sec);
        write(fd, &time, strlen(time));

        //sleep
        sleep(30);

        //liberamos el cerrojo
        lock.l_type = F_UNLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        lock.l_pid = getpid();

        if(fcntl(fd, F_SETLK, &lock) == -1){
          close(fd);
          printf("Error %ui: %s", errno, strerror(errno));
          exit(EXIT_FAILURE);
        }
      }
      else{
        close(fd);
        printf("Error %ui: %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
      }
    }
    else{
      printf("Fichero bloqueado\n");
      exit(EXIT_SUCCESS);
    }
  }
  else{
    close(fd);
    printf("Error %ui: %s", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
