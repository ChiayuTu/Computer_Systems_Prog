CC=gcc
# flag all warnings. default optimization level.
CFLAGS=-Wall -Og
# set up for use in gdb
DFLAGS=-g
# For additional libraries, e.g. -lm
LDFLAGS=
PROGS=main

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -f $(PROGS) *.o ~*
