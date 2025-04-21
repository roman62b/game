# Makefile
CC=gcc
CFLAGS=-C -Wall

all:
	$(CC) $(CFLAGS) game.c sysapi.c -o game
