#include <stdio.h>
#include <stdlib.h>
#include "fail.h"

void fail(char *path, char *reason,int should_perror) {
  if (should_perror)
    perror(path);
  else
    fprintf(stderr, reason, path);
  exit(1);
}
