#include <string.h>
// Librerias para la gestion de errores
#include <stdio.h>
#include <errno.h>
// Librerias para el setuid
#include <sys/types.h>
#include <unistd.h>

int main () {

  for(int i = 0; i < 255; i++)
    printf("Cadena de error %i: %s\n", i, strerror(i));

  return 1;
}
