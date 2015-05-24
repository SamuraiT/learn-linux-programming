CC = gcc
CFLAGS = -Wall -g
grep: grep.c
	$(CC) $(CFLAGS) -o $@ $<

ls: ls.c
	$(CC) $(CFLAGS) -o $@ $<
