#include <string.h>
// Librerias para la gestion de errores
#include <stdio.h>
#include <errno.h>
// Librerias para el setuid
#include <sys/types.h>
#include <unistd.h>

int main () {
  int errno;
  char *s;

  if (setuid(0) == -1)
    perror(s);
    
  printf("Código de error: %i\n", errno);
  printf("Cadena de error: %s\n", strerror(errno));

  return 1;
}
