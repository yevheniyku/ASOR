#include <sys/utsname.h>
#include <string.h>
// Librerias para la gestion de errores
#include <stdio.h>
#include <errno.h>
// Librerias para el setuid
#include <sys/types.h>
#include <unistd.h>

int main(){
  struct utsname buf;

  if(uname(&buf) == -1){
    printf("Error %i: %s\n", errno, strerror(errno));
    return -1;
  }

  printf("Nombre del sistema: %s\n", buf.sysname);
  printf("Nombre del nodo: %s\n", buf.nodename);
  printf("Release: %s\n", buf.release);
  printf("Versión: %s\n", buf.version);

  return 1;
}
