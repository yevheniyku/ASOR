#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){

  int id, eid;
  // UID real
  id = getuid();
  // UID efectivo
  eid = geteuid();

  printf("El ID del ususario: %i\n", id);
  printf("El EID del usuario: %i\n", eid);

  /*
  EXPLICACIÓN DE BORJA:
  
    El setuid se utiliza para dar privilegios elevados en
    determinados archivos para usuarios que no lo poseen,
    como por ejemplo en el archivo /etc/bin/passwd para
    que todos puedan cambiar la contraseña pero que no puedan
    leer ni escribir las otras. Por lo tanto, cuando el uid es
    distinto del euid tiene el bit setuid activado.
  */

  return 1;
}
