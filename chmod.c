#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fail.h"

int main(int argc, char *argv[]) {
  int mode, i;
  if (argc < 2) fail(argv[0], "%s: wrong arguments", USE_FPRINTF);
  mode = strtol(argv[1], NULL, 8);
  for (i=2; i < argc; i++)
    chmod(argv[i], mode) < 0 ? fail(argv[i], "", USE_PERROR) : NULL;

  return 0;
}
