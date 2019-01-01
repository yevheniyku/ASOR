// uname
#include <sys/utsname.h>
// errores
#include <string.h>
#include <stdio.h>
#include <errno.h>


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
