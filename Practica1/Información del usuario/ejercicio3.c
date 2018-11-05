#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

int main(){

  unsigned int id, eid;
  int errno;

  id = getuid();
  eid = geteuid();

  printf("El ID del ususario: %i\n", id);
  printf("El EID del usuario: %i\n", eid);

  struct passwd p;
  p = *getpwuid(id);

  printf("Nombre de usuario: %s\n", p.pw_name);
  printf("Directorio Home: %s\n", p.pw_dir);
  printf("Descripción de usuario: %s\n", p.pw_gecos);
  
  return 1;
}
