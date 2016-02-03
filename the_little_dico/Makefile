CC=gcc
CFLAGS=-Wall #-DDEBUG

all: dico.out

dico.out: dico.o menu.o main.o
	$(CC) -o dico.out dico.o menu.o main.o

dico.o: dico.h dico.c
	$(CC) $(CFLAGS) -o dico.o -c dico.c

menu.o: menu.h dico.h menu.c
	$(CC) $(CFLAGS) -o menu.o -c menu.c

main.o: dico.h menu.h main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o; rm -rf *.out
