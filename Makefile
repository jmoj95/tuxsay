INCDIR = ./include
BINDIR = ./bin
SRCDIR = ./src
CC = g++

all:
	${CC} -I${INCDIR} ${SRCDIR}/* -o ${BINDIR}/main

clean:
	rm ${BINDIR}/* 
