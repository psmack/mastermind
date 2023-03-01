# Makefile for Mastermind Game

all:  mastermind 

mastermind: mastermind.c
	gcc -std=c11 -Wall -Wextra -Wpedantic -Wwrite-strings -Wfloat-equal -o mastermind mastermind.c

debug: 
	gcc -g -std=c11 -Wall -Wextra -Wpedantic -Wwrite-strings -Wfloat-equal -o mastermind mastermind.c

clean:
	rm mastermind *.o *.a *.so
