#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void head(FILE *f, long nlines);
static void head_files(char *path, long nlines);

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
  {"lines", required_argument, NULL, 'n'},
  {"help", no_argument, NULL, 'h'},
  {0,0,0,0}
};

int main(int argc, char *argv[]) {
  int opt;
  long nlines = DEFAULT_N_LINES;

  while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1) {
    switch(opt) {
      case 'n':
        nlines = atoi(optarg);
        break;
      case 'h':
        fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
        exit(0);
      case '?':
        fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
        exit(1);
    }
  }

  if (optind == argc) {
    head(stdin, nlines);
  } else {
    int i;
    for (i=optind; i < argc; i++)
      head_files(argv[i], nlines);
  }
  exit(0);
}

static void head_files(char *path, long nlines) {
  int i;
  FILE *f;
  f = fopen(path, "r");
  if (!f) {perror(path); exit(1);}
  head(f, nlines);
  fclose(f);
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
