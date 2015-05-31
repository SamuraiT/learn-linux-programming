#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
int main(void) {

  char buf[2048];

  printf("cwd: %s \n", getcwd(buf, sizeof buf));
  chdir("..");
  printf("cwd: %s \n", getcwd(buf, sizeof buf));
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  printf("%ld , %ld , \n",usage.ru_ixrss, usage.ru_maxrss);
  time_t _time;
  printf("%lld \n", (long long) time(&_time));
  printf("time: %s\n", ctime(&_time));
  exit(0);
}
