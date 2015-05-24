CC = gcc
CFLAGS = -Wall -g
grep: grep.c
	$(CC) $(CFLAGS) -o $@ $<
