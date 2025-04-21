# Makefile

CC=gcc
CFLAGS=-C -Wall

all:
	$(CC) $(CFLAGS) game.c sysapi.c -o bin/game

# make it done tomorrow

#install:
#	mv /bin/game /usr/local/bin/game

#all: game

#game: game.o sysapi.o
#	$(CC) game.o sysapi.o -o game

#game.o: game.c
#	$(CC) $(CFLAGS) -c game.c

#sysapi.o: sysapi.c
#	$(CC) $(CFLAGS) -c sysapi.c

#clean:
#	rm -rf *.o game
