CC=gcc
CFLAGS=-Wall -DDEBUG

all: binom.out

binom.out: binom.o main.o menu.o
	$(CC) -o binom.out binom.o main.o menu.o

binom.o: binom.h binom.c
	$(CC) $(CFLAGS) -o binom.o -c binom.c

menu.o: binom.h menu.h menu.c
	$(CC) $(CFLAGS) -o menu.o -c menu.c

main.o: binom.h main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o; rm -rf *.out
