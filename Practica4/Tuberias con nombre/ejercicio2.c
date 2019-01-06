#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int errno;

  if (argc != 2) {
   fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
   exit(EXIT_FAILURE);
  }

  int fifo = mkfifo(argv[1], 0777);

  if(fifo != -1){
    int fd = open(argv[1], O_WRONLY);

    if(fd != -1){
      write(fd, argv[1], strlen(argv[1]));
    }
    else{
      printf("Error: %i\n %s", errno, strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  else{
    printf("Error: %i\n %s", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
