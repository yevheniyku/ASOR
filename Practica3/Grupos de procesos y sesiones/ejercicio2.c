#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/resource.h>

int main(){
  unsigned int maxFiles;
  struct rlimit limit;
  char buffer[512];

  pid_t pid  = getpid();
  pid_t ppid = getppid();
  pid_t gpid = getpgid(pid);
  pid_t sid  = getsid(pid);

  getcwd(buffer, sizeof(buffer));
  getrlimit(RLIMIT_NOFILE, &limit);

  printf("ID del proceso: %u\n", pid);
  printf("ID del proceso padre: %u\n", ppid);
  printf("ID del grupo de procesos: %u\n", gpid);
  printf("ID de la sesion: %u\n", sid);
  printf("Directorio de trabajo: %s\n", buffer);
  printf("Numero maximo de ficheros abiertos: %lu\n", limit.rlim_max);

  return 1;
}
