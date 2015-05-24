#include <stdio.h>
#include <unistd.h>
#include "fail.h"

int main(int argc, char *argv[]) {
  int i;
  if (argc < 2) fail(argv[0], "%s: No arguments\n", 0);
  for (i=1; i < argc; i++)
    if(rmdir(argv[i]) < 0) fail(argv[i], "", 1);

  return 0;
}
