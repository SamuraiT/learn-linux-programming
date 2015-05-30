#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "fail.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void sig_handler(int signo) {

  if (signo == SIGINT) {
    printf("hogehoge bar \n");
    exit(0);
  }
}
typedef void (*sighandler_t)(int);

sighandler_t trap_signal(int sig, sighandler_t handler){
  struct sigaction act, old;

  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  if (sigaction(sig, &act, &old) < 0)
    return NULL;
  return old.sa_handler;
}

int main(void) {
  trap_signal(SIGINT, sig_handler);
  pid_t pid;
  pid = fork();
  if (pid > 0) {
    int status;
    pause();
    waitpid(pid, &status, 0);
  } else {
    while(1){
      printf("hoge\n") ;
      sleep(2);
    }
  }
  exit(0);
}
