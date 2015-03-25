CC=gcc
CPPFLAGS=
CFLAGS= -std=c99 -Wall -pedantic -Iinclude -g
LDFLAGS=

all: src/*
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/holes

clean: 
	rm bin/*
