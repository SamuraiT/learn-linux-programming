#include <stdio.h>
#include "fail.h"

int main(int argc, char *argv[]) {
  if (argc != 3) fail(argv[0], "%s: wrong number of arguments\n", USE_FPRINTF);
  if(rename(argv[1], argv[2]) < 0) fail(argv[1], "", USE_PERROR);
  return 0;
}
