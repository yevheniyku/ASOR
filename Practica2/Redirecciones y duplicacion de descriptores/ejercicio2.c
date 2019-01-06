#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
  int errno;
  char *s;

  if (argc != 2) {
   fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
   exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

  if(fd == -1){
    printf("ERROR %ui: %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  int fd2 = dup2(fd, 1);
  int fd3 = dup2(fd, 2);

  printf("La salida redireccionada a %s\n", argv[1]);

  if(setuid(0) == -1) perror(s);

  dup2(fd2, fd);
  dup2(fd3, fd);

  exit(EXIT_SUCCESS);
}
