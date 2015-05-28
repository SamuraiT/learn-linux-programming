#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "fail.h"

int main(int argc, char *argv[]) {
  pid_t pid;
  if (argc != 3) fail(argv[0], "Usage: %s <commad> <arg>\n", USE_FPRINTF);
  pid = fork();
  printf("pid: %d\n", pid);
  if (pid < 0) fail(argv[0], "fork(2) failed\n", USE_PERROR);
  if (pid == 0) {
    execl(argv[1], argv[1], argv[2], NULL);
    perror(argv[1]);
    exit(99);
  } else {
    int status;
    waitpid(pid, &status, 0);
    printf("child (PID=%d) finished", pid);
    if (WIFEXITED(status))
      printf("exit, status=%d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
      printf("signal, sig=%d\n", WTERMSIG(status));
    else
      printf("abnormal exit\n");
    exit(0);
  }
}
