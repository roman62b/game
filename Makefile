# Makefile

CC=gcc
CFLAGS=-C -Wall

all:
	$(CC) $(CFLAGS) game.c sys_utils.c dbg_utils.c -o bin/game

install:
	mv bin/game /usr/local/bin/game
