CC = gcc
CFLAGS = -g -Wall -I./include

vpath %.c src
vpath %.h include

bin/main:	main.c bst/bst.h bst/bst_node.h list/list.h deque.h heap.h queue.h red-black-tree/tree.h red-black-tree/node.h stack.h
	${CC} ${CFLAGS} -o $@ $<

clean:
	-rm -f bin/main
