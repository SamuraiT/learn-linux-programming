#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);
static void pprint_fd(int fd);
static void cat(int fd);

int main(int argc, char *argv[]){
  int i;
  int fd;
  if (argc == 1){
    cat(STDIN_FILENO);
  } else {
    for (i=1; i < argc; i++){
      fd = open(argv[i], O_RDONLY);
      if (!fd) { perror(argv[i]); exit(1); }
      cat(fd);
    }
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void cat(int fd) {
  unsigned char buf[BUFFER_SIZE];
  int n = 1;
  while (n != 0) {
    n = read(fd, buf, sizeof buf);
    write(STDOUT_FILENO, buf, n);
  }
}

static void do_cat(const char *path){
  int fd;
  unsigned char buf[BUFFER_SIZE];
  int n;
  fd = open(path, O_RDONLY);
  if (fd < 0) die(path);
  for (;;){
    n = read(fd, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    if (write(STDOUT_FILENO, buf, n) < 0) die(path);
  }
  if (close(fd) < 0) die(path);
}

static void die(const char *s){
  perror(s);
  exit(1);
}

static void pprint_fd(int fd){
  printf("--------\n");
  printf("%d\n", fd);
  printf("--------\n");
}
