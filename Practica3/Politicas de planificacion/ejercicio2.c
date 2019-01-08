#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){

  pid_t id = getpid();
  int sched_policy, priority;
  int errno;

  sched_policy = sched_getscheduler(id);

  switch(sched_policy){
    case SCHED_OTHER:
      printf("Actual sched policy: SCHED_OTHER\n"); break;
    case SCHED_FIFO:
      printf("Actual sched policy: SCHED_FIFO\n"); break;
    case SCHED_RR:
      printf("Actual sched policy: SCHED_RR\n"); break;
    default:
      printf("ERROR %i: %s\n", errno, strerror(errno)); break;
  }

  priority = getpriority(PRIO_PROCESS, 0);
  printf("Priority: %i\n", priority);
  printf("Min priority: %i\n", sched_get_priority_min(sched_policy));
  printf("Max priority: %i\n", sched_get_priority_max(sched_policy));


  return 1;
}
