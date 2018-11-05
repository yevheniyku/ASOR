#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
  int errno;
  time_t t = time(NULL);

  if(t != -1){
      printf("Segundos desde el Epoch: %ld\n", t);
  }
  else{
    printf("ERROR %i: %s", errno, strerror(errno));
  }

  return 1;
}
