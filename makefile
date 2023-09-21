#Macros
CC = gcc
FLAG = -Wall -g

all: main

clean:
	rm -f main *.o

main:  main.o functions.o
	$(CC) $(FLAG) $< functions.o -o $@

main.o: main.c functions.h
	$(CC) $(FLAG) -c $<

functions.o: functions.c functions.h
	$(CC) $(FLAG) -c $<