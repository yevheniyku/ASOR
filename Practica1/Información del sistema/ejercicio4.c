// errores
#include <string.h>
#include <stdio.h>
#include <errno.h>
// pathconf
#include <unistd.h>

int main(){
  int info[3] = {_PC_LINK_MAX, _PC_PATH_MAX, _PC_NAME_MAX};

  printf("Número máximo de enlaces: %li\n", pathconf("/", info[0]));
  printf("Longitud máxima de ruta: %li\n", pathconf("/", info[1]));
  printf("Longitud máxima de nombre: %li\n", pathconf("/", info[2]));

  return 1;
}
