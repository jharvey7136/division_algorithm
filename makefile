# John Harvey


#CONSTANTS
CC = gcc
RUN = ./all
#CFLAGS = -g
# CFLAGS = -ansi -pedantic -Wall -g -DDEBUG

all: DivAlg.o
	${CC} -o all DivAlg.o

DivAlg.o : DivAlg.c
	${CC} ${CFLAGS} -c DivAlg.c

run: all
	 ${RUN}

#clean = clean will remove object files and executables
clean:
	rm -rf *.o *.out all
