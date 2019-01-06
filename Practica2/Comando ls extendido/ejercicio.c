#include <error.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {

  if (argc != 2) {
   fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
   exit(EXIT_FAILURE);
  }

  DIR *dir = opendir(argv[1]);

  if(dir == NULL){
    perror("Error a la hora de abrir el directorio");
    exit(EXIT_FAILURE);
  }

  struct dirent *cur;
  struct stat sb;
  cur = readdir(dir);
  long int totalsize = 0;

  while(cur != NULL){
    size_t pathsize = strlen(argv[1]);
    char *path = malloc(sizeof(char) * (pathsize + strlen(cur->d_name) + 3));
    strcpy(path, argv[1]);
    strcat(path, "/");
    strcat(path, cur->d_name);

    if(stat(path, &sb) != -1){
      if(S_ISREG(sb.st_mode)){
        printf("[FICHERO_REG]: %s\n", cur->d_name);
        totalsize = totalsize + ((sb.st_blksize/8)*sb.st_blocks);
        free(path);
      }
      else if(S_ISDIR(sb.st_mode)){
        printf("[DIR]: %s\n", cur->d_name);
      }
      else if(S_ISLNK(sb.st_mode)){
        char *link = malloc(sb.st_size + 1);
        int rc2 = readlink(path, link, sb.st_size + 1);
        printf("[ENLACE]: %s->%s \n", cur->d_name, link);
        free(link);
      }
    }
    else{
      perror("Error a la hora de obtener informacion sobre el archivo");
      free(path);
      closedir(dir);
      exit(EXIT_FAILURE);
    }

     cur = readdir(dir);
  }

  closedir(dir);

  return 0;
}
