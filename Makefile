CC = gcc
CFLAGS = -Wall -g
grep: grep.c
	$(CC) $(CFLAGS) -o $@ $<

ls: ls.c
	$(CC) $(CFLAGS) -o $@ $<

mkdir: mkdir.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

rmdir: rmdir.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

