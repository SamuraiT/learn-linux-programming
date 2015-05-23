#include <stdio.h>
#include <stdlib.h>
/*
 * cat with stdio
 *
 */
#define TAB '\t'
#define LINE_BREAK '\n'
typedef int bool;
#define true 1
#define false 0
#define _GNU_SOURCE
#include <getopt.h>

void print_escaped_tab();
void print_escaped_line_break();

static struct option longopts[] = {
  {"literal", no_argument, NULL, 'l'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
  int opt;
  bool should_show_literal = false;

  while((opt = getopt_long(argc, argv, "l", longopts, NULL)) != -1){
    switch (opt) {
      case 'l':
        should_show_literal = true;
        break;
      case '?':
        fprintf(stderr, "Usage: %s [l]\n", argv[0]);
        exit(1);
    }
  }

  int i;
  for (i=optind; i < argc; i++){
    FILE *f;
    int c;
    f = fopen(argv[i], "r");
    if (!f) { perror(argv[i]); exit(1); }
    while ( (c = fgetc(f)) != EOF) {
      if (should_show_literal) {
        if ( c == TAB ) { print_escaped_tab(); continue; }
        if ( c == LINE_BREAK ) { print_escaped_line_break(); continue; }
      }
      if (putchar(c) < 0) exit(1);
    }
    fclose(f);
  }
  exit(0);
}

void print_escaped_tab () {
  int slash = 92;
  int t = 116;
  if (putchar(slash) < 0) exit(1);
  if (putchar(t) < 0) exit(1);
}

void print_escaped_line_break () {
  int dollar = 32;
  int slash = 92;
  int n = 110;
  if (putchar(dollar) < 0) exit(1);
  if (putchar(slash) < 0) exit(1);
  if (putchar(n) < 0) exit(1);
}
