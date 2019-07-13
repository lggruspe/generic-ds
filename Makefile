CC = gcc
CFLAGS = -g -Wall -I./include
TESTS = $(patsubst test/%.c,bin/test_%,$(wildcard test/*.c))

vpath %.c src
vpath %.h include

bin/main:	main.c bst/bst.h bst/bst_node.h heap.h red-black-tree/tree.h red-black-tree/node.h 
	${CC} ${CFLAGS} -o $@ $<

.PHONY:	clean
clean:
	-rm -f bin/main

$(TESTS):	bin/test_%: test/%.c %.h test/test_lib.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:	test
test:	$(TESTS)
	for TEST in $^; do\
		./$$TEST;\
	done
