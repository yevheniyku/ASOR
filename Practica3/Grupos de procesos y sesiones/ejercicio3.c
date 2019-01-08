#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>

int processInfo(char * proc){
  unsigned int maxFiles;
  struct rlimit limit;
  char buffer[512];

  pid_t pid  = getpid();
  pid_t ppid = getppid();
  pid_t gpid = getpgid(pid);
  pid_t sid  = getsid(pid);

  getcwd(buffer, sizeof(buffer));
  getrlimit(RLIMIT_NOFILE, &limit);

  printf("ID del proceso %s:                  %u\n", proc, pid);
  printf("ID del proceso padre del %s:        %u\n", proc, ppid);
  printf("ID del grupo de procesos del %s:    %u\n", proc, gpid);
  printf("ID de la sesion del %s:             %u\n", proc, sid);
  printf("Directorio de trabajo del %s:       %s\n", proc, buffer);
  printf("Maximo de ficheros abiertos del %s: %lu\n", proc, limit.rlim_max);

  return 0;
}

int main(){
  pid_t pid = fork();
  pid_t sid;

  switch (pid) {
    case -1: perror("No se ha podido hacer el fork"); break;
    case 0:
      sid = setsid();
      chdir("/tmp");
      processInfo("Hijo");
      break;
    default:
      processInfo("Padre");
      int status;
      wait(&status);
      break;
  }

  return 0;
}
