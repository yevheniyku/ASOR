#include <stdio.h>
#include <string.h>
//error
#include <errno.h>
// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
  int errno;

  // quitamos los permisos de ejecucion a los grupos
  // y todos los permisos a otros
  umask(0027);

  if(open("new_file", O_CREAT | O_RDONLY, 0777) == -1)
    printf("Error: %i\n %s", errno, strerror(errno));

  // permisos por defecto (022)
  umask(0022);

  return 0;
}
