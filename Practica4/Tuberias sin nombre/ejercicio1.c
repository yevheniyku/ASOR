#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
  int pipefd[2];
  pid_t cpid;
  char buf;

  if (argc != 5) {
    fprintf(stderr, "Usage: %s <command1> <argument1> <command2> <argument2>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  cpid = fork();
  int newFD;
  
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  switch (cpid) {
		case 0:
			close(pipefd[1]);
			newFD = dup2(pipefd[0], 0);
			close(pipefd[0]);
			execlp(argv[3], argv[3], argv[4], NULL);
		break;

		default:
			close(pipefd[0]);
			newFD = dup2(pipefd[1], 1);
			close(pipefd[1]);
			execlp(argv[1], argv[1], argv[2], NULL);
  }

  return 0;
}
