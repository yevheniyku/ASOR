#include <stdio.h>
#include <string.h>
//error
#include <errno.h>
// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
  int errno;

  if(open("new_file", O_CREAT, 00645) == -1)
    printf("Error: %i\n %s", errno, strerror(errno));

  return 0;
}
