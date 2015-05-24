#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "fail.h"

int main(int argc, char *argv[]) {
  int i;
  if (argc < 2) fail(argv[0], "%s: No arguments\n", 0);
  for (i=1; i < argc; i++)
    if(mkdir(argv[i], 0777) < 0) fail(argv[i], "", 1);
  exit(0);
}


