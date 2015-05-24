#include <stdio.h>
#include <unistd.h>
#include "fail.h"

int main(int argc, char *argv[]) {
  if (argc != 3) fail(argv[0], "%s: wrong number of argument", 0);
  if (symlink(argv[1], argv[2]) < 0) fail(argv[1], "", 1);
  return 0;
}
