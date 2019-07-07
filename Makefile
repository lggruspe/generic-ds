CC = gcc
CFLAGS = -g -Wall -I./include

bin/main:	src/main.c
	${CC} ${CFLAGS} -o bin/main src/main.c

clean:
	rm bin/main
