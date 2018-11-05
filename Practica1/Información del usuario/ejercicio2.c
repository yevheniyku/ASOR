#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){

  int id, eid;

  id = getuid();
  eid = geteuid();

  printf("El ID del ususario: %i\n", id);
  printf("El EID del usuario: %i\n", eid);

  return 1;
}
