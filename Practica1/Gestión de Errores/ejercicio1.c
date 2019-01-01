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

  /*
    setuid(0) asigna el UID efectivo, en este caso UID=0 (root)
    al proceso que hace la llamada
  */
  if (setuid(0) == -1){
    perror(s);
  }


  return 1;
}
