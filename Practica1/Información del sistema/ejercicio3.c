#include <string.h>
// Librerias para la gestion de errores
#include <stdio.h>
#include <errno.h>
// Librerias para el setuid
#include <sys/types.h>
#include <unistd.h>

int main(){
  int info[3] = {_SC_ARG_MAX, _SC_CHILD_MAX, _SC_OPEN_MAX};

  printf("Número máximo de argumentos: %li\n", sysconf(info[0]));
  printf("Número máximo de hijos: %li\n", sysconf(info[1]));
  printf("Número máximo de ficheros: %li\n", sysconf(info[2]));

  return 1;
}
