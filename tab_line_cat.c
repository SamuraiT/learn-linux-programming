#include <stdio.h>
#include <stdlib.h>
/*
 * cat with stdio
 *
 */
#define TAB 9
#define LINE_BREAK 10

void print_escaped_tab();
void print_escaped_line_break();

int main(int argc, char *argv[]) {
  int i;
  for (i=1; i < argc; i++){
    FILE *f;
    int c;
    f = fopen(argv[i], "r");
    if (!f) { perror(argv[i]); exit(1); }
    while ( (c = fgetc(f)) != EOF) {
      if ( c == TAB ) { print_escaped_tab(); continue; }
      if ( c == LINE_BREAK ) { print_escaped_line_break(); continue; }
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
  if (putchar(32) < 0) exit(1);
  if (putchar(92) < 0) exit(1);
  if (putchar(110) < 0) exit(1);
}
