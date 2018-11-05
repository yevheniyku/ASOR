#include <time.h>
#include <stdio.h>

int main(){

  const time_t t = time(NULL);
  struct tm *lt = localtime(&t);

  printf("Año: %i\n", 1900+lt->tm_year);

  return 1;
}
