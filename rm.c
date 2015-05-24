#include <stdio.h>
#include <unistd.h>
#include "fail.h"

int main(int argc, char *argv[]) {
  int i;
  if (argc < 2) fail(argv[0], "%s: No arguments\n", USE_FPRINTF);

  for (i=1; i < argc; i++)
    if(unlink(argv[i]) < 0) fail(argv[i], "", USE_PERROR);
  return 0;
}
