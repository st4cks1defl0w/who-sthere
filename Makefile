.PHONY: cleantest

CC ?= gcc
CFLAGS += -Wall -pedantic -O2 -g

all: clean who-sthere stats

mlisp89: mlisp89.c
	$(CC) $(CFLAGS) -ansi -D_DEFAULT_SOURCE -o $@ $^

stats: who-sthere.c
	wc $^

clean:
	@rm -fv who-sthere
