#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]){
  // estructura que contiene la información requerida
  struct stat sb;

  if (argc != 2) {
   fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
   exit(EXIT_FAILURE);
  }

  // obtenemos la información
  if (stat(argv[1], &sb) == -1) {
   perror("stat");
   exit(EXIT_FAILURE);
  }

  //sacamos los números major y minor
  printf("Major: %lx\nMinor: %lx\n",
    (long) major(sb.st_dev), (long) minor(sb.st_dev));

  printf("Tipo de fichero:             ");

  switch (sb.st_mode & S_IFMT) {
    case S_IFDIR:  printf("Directorio\n");              break;
    case S_IFLNK:  printf("Enlace Simbolico\n");        break;
    case S_IFREG:  printf("Fichero Regular\n");         break;
    default:       printf("unknown?\n");                break;
  }
  //numero de inodo
  printf("Número de i-nodo:            %ld\n", (long) sb.st_ino);
  //último acceso
  printf("Last file access:            %s", ctime(&sb.st_atime));

  /*
    st_atime: fecha de último acceso
    st_ctime: fecha del último cambio de propietario del fichero, grupo, modo, etc
    st_mtime: fecha de la última modificación
  */
  exit(EXIT_SUCCESS);
}
