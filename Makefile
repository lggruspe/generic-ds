CC = gcc
CFLAGS = -g -Wall -I./include

vpath %.c src
vpath %.h include

bin/main:	main.c bst/bst.h bst/bst_node.h list/list.h deque.h heap.h queue.h red-black-tree/tree.h red-black-tree/node.h stack.h
	${CC} ${CFLAGS} -o $@ $<

.PHONY:	clean
clean:
	-rm -f bin/main

bin/test_stack:	test/stack.c stack.h
	${CC} ${CFLAGS} -o $@ $<

.PHONY:	test
test:	bin/test_stack
	./bin/test_stack
