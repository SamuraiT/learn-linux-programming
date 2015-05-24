#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static struct option longopts[] = {
  {"ignore-case", required_argument, NULL, 'i'},
  {"invert-match", required_argument, NULL, 'v'},
  {0,0,0,0}
};

typedef void (* GREP_POINTER)(regex_t *pattern, FILE *src);
static void grep(regex_t *pattern, FILE *src);
static void grep_files(regex_t *pattern, char *path, GREP_POINTER _grep);
static void reg_error(int err, regex_t *pattern);
static void invert_grep(regex_t *pattern, FILE *src);

int main(int argc, char *argv[]) {
  regex_t pattern;
  char *pat = '\0';
  int err, opt, i;
  GREP_POINTER _grep = grep;
  while ((opt = getopt_long(argc, argv, "i:v:", longopts, NULL)) != -1) {
    switch (opt) {
      case 'i':
        pat = optarg;
        break;
      case 'v':
        pat = optarg;
        _grep = invert_grep;
        break;
      case '?':
        fprintf(stdout, "Usage: %s [-i, -v] [FILE ...]\n", argv[0]);
        exit(1);
    }
  }
  if (!pat) pat = argv[optind];
  if (argc < 2) { fputs("no pattern\n", stderr); exit(1); }
  err = regcomp(&pattern, pat, REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
  if (err != 0) reg_error(err, &pattern);
  if (argc == optind) { _grep(&pattern, stdin);}
  else {
    for (i=optind; i < argc; i++)
      grep_files(&pattern, argv[i], _grep);
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

static void invert_grep(regex_t *pattern, FILE *src) {
  char buf[4096];
  while (fgets(buf, sizeof buf, src)) {
    if (regexec(pattern, buf, 0, NULL, 0) != 0)
      fputs(buf, stdout);
  }
}


static void grep_files(regex_t *pattern, char *path, GREP_POINTER _grep) {
  FILE *f;
  f = fopen(path, "r");
  if(!f) { perror(path); exit(1); }
  _grep(pattern, f);
  fclose(f);
}


