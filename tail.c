#include <stdio.h>
#include <stdlib.h>
static void tail(char *path, off_t n);

int main(int argc, char *argv[]) {
  off_t n = 18;
  int byte = 8;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [File, File, ..]", argv[1]);
    exit(1);
  }
  int i;
  for (i=1; i < argc; i++) {
    tail(argv[i], n*byte);
  }
  exit(0);
}

static void tail(char *path, off_t n) {
  FILE *f;
  int c;
  f = fopen(path, "r");
  fseek(f, -n, SEEK_END);
  while ( (c = getc(f)) != EOF ) {
    if(putchar(c) < 0) exit(0);
  }

}
