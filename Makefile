# Makefile

CC=gcc
CFLAGS=-C -Wall

all:
	$(CC) $(CFLAGS) src/game.c src/sys_utils.c src/dbg_utils.c -o bin/game

install:
	mv bin/game /usr/local/bin/game
