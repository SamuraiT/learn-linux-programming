#include <stdio.h>
#include <stdlib.h>
#define LINE_BREAK 10

int main(int argc, char *argv[]) {
  int i;
  int count = 0;
  for (i=1; i < argc; i++) {
    FILE *f;
    int c;
    f = fopen(argv[i], "r");
    if (!f) { perror(argv[i]); exit(1);}
    while ( (c = fgetc(f)) != EOF){
      if (c == LINE_BREAK) count++;
    }
  }
  printf("%d\n", count);
  exit(0);
}
