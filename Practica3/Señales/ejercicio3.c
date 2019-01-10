#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  sigset_t signals;

  if(sigemptyset(&signals) == -1){
    perror("No se ha podido crear un empty set");
  }
  if(sigaddset(&signals, SIGINT) == -1){
    perror("No se ha podido agregar SIGINT al set");
  }
  if(sigaddset(&signals, SIGTSTP) == -1){
    perror("No se ha podido agregar SIGTSTP al set");
  }
  if(sigprocmask(SIG_BLOCK, &signals, NULL) == -1){
    perror("No se ha podido agregar la mascara al set");
  }

/*

  #En mi distro no existe esta variable de entorno

  char * sleepsecs = getenv("SLEEP_SECS");
  int sleep_secs = atoi(sleepsecs);
*/
  sleep(10);

  sigset_t check;
  sigemptyset(&check);
  sigpending(&check);

  if(sigismember(&check, SIGINT)){
    printf("Señal SIGINT pendiente de recibir\n");
  }
  else if(sigismember(&check, SIGTSTP)){
    printf("Señal SIGSTP pendiente de recibir\n");
  }
  else{
    sigprocmask(SIG_UNBLOCK, &signals, NULL);
    printf("Señales desbloqueadas\n");
  }

  return 0;
}
