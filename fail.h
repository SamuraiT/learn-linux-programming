#ifndef FAIL_H_
#define FAIL_H_
static int const USE_PERROR = 1;
static int const USE_FPRINTF = 0;

void fail(char *path, char *reason,int should_perror);
#endif
