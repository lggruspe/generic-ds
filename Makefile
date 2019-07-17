CC = gcc
CFLAGS = -g -Wall -I./include
TESTS = $(patsubst test/%.c,bin/test_%,$(wildcard test/*.c))

vpath %.c src
vpath %.h include

all:	$(TESTS)

$(TESTS):	bin/test_%: test/%.c %.h test/test_lib.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:	clean
clean:
	-rm -f bin/main bin/test_* vgcore.*

.PHONY:	test
test:	$(TESTS)
	for TEST in $^; do\
		./$$TEST;\
	done

.PHONY:	leaktest
leaktest:	$(TESTS)
	for TEST in $^; do\
		valgrind --leak-check=full --log-file="debug/$(patsubst bin/%,%,$$TEST)" $$TEST;\
	done
