#include <stdio.h>
#include <stdlib.h>

static void head(FILE *f, long nlines);
static void head_files(char *path, long nlines);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    exit(1);
  }
  long nlines = atol(argv[1]);

  if (argc >= 3) {
    int i;
    for (i=2; i < argc; i++)
      head_files(argv[i], nlines);
  } else {
    head(stdin, nlines);
  }
  exit(0);
}

static void head_files(char *path, long nlines) {
  int i;
  FILE *f;
  f = fopen(path, "r");
  if (!f) {perror(path); exit(1);}
  head(f, nlines);
}

static void head(FILE *f, long nlines) {
  int c = 0;
  if (nlines <= 0) return;
  while((c = getc(f)) != EOF) {
    if (putchar(c) < 0) exit(1);
    if (c == '\n') {
      nlines--;
      if (nlines == 0) return;
    }
  }
}
