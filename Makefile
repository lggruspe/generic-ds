CC = gcc
CFLAGS = -g -Wall -I./include

bin/main:	src/main.c include/bst/bst.h include/bst/bst_node.h include/list/list.h include/deque.h include/heap.h include/queue.h include/red-black-tree/tree.h include/red-black-tree/node.h include/stack.h
	${CC} ${CFLAGS} -o bin/main src/main.c

clean:
	rm bin/main
