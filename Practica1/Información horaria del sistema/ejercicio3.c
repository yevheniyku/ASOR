#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(){
  struct timeval tv1, tv2;
  struct timezone tz;

  if(gettimeofday(&tv1, NULL) == -1){
    printf("ERROR %i: %s", errno, strerror(errno));
    return -1;
  }

  int i = 0;

  while(i < 1000000){
    i++;
  }

  if(gettimeofday(&tv2, NULL) == -1){
    printf("ERROR %i: %s", errno, strerror(errno));
    return -1;
  }

  printf("Se ha tardado %li milisegundos\n", tv2.tv_usec - tv1.tv_usec);
  return 1;
}
