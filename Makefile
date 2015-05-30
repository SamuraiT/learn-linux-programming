CC = gcc
CFLAGS = -Wall -g
error_printer=fail.c
command = $(CC) $(CFLAGS) -o $@ $< $(error_printer)

grep: grep.c
	$(CC) $(CFLAGS) -o $@ $<

ls: ls.c
	$(CC) $(CFLAGS) -o $@ $<

mkdir: mkdir.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

rmdir: rmdir.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

ln: ln.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

lns: symlink.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

rm: rm.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

mv: mv.c
	$(CC) $(CFLAGS) -o $@ $< fail.c

chmod: chmod.c
	$(command)

lsr: traverse.c
	$(command)

try: try_rename.c
	$(command)

spawn: spawn.c
	$(command)

shell: shell.c
	$(command)

stop: stop.c
	$(command)
