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

int main(void) {
  if(signal(SIGINT, sig_handler) < 0) fail(".", "Handler ERROR \n", USE_PERROR);
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
