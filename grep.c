#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

static void grep(regex_t *pattern, FILE *src);
static void grep_files(regex_t *pattern, char *path);
static void reg_error(int err, regex_t *pattern);

int main(int argc, char *argv[]) {
  regex_t pattern;
  int err;
  int i;
  if (argc < 2) { fputs("no pattern\n", stderr); exit(1); }

  err = regcomp(&pattern, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
  if (err != 0) reg_error(err, &pattern);
  if (argc == 2) { grep(&pattern, stdin); }
  else {
    for (i=2; i < argc; i++)
      grep_files(&pattern, argv[i]);
  }
  regfree(&pattern);
  exit(0);
}

static void reg_error(int err, regex_t *pattern) {
  char buf[1024];
  regerror(err, pattern, buf, sizeof buf);
  puts(buf);
  exit(1);
}

static void grep(regex_t *pattern, FILE *src) {
  char buf[4096];
  while (fgets(buf, sizeof buf, src)) {
    if (regexec(pattern, buf, 0, NULL, 0) == 0)
      fputs(buf, stdout);
  }
}

static void grep_files(regex_t *pattern, char *path) {
  FILE *f;
  f = fopen(path, "r");
  if(!f) { perror(path); exit(1); }
  grep(pattern, f);
  fclose(f);
}


