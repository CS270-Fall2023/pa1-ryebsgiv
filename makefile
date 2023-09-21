main:  main.o functions.o
	gcc functions.o main.o -o main

main.o: main.c functions.h
	gcc -c main.c

functions.o: functions.c functions.h
	gcc -c functions.c