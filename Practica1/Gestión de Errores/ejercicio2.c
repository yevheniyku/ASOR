// errores
#include <stdio.h>
#include <string.h>
#include <errno.h>
// setuid
#include <sys/types.h>
#include <unistd.h>

int main () {
  int errno;
  char *s;

  if (setuid(0) == -1){
    printf("Código de error: %i\n", errno);
    printf("Cadena de error: %s\n", strerror(errno));
  }

  return 1;
}
