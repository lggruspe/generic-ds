check_PROGRAMS = test/test_heap test/test_list test/test_queue test/test_rbtree test/test_vector
# test/heap_m
# test/bst

test_test_bst_SOURCES = test/bst.c include/bst.h test/test_lib.h
test_test_heap_SOURCES = test/heap.c include/heap.h test/test_lib.h
test_test_heap_m_SOURCES = test/heap_m.c include/heap_m.h test/test_lib.h
test_test_list_SOURCES = test/list.c include/list.h test/test_lib.h
test_test_queue_SOURCES = test/queue.c include/queue.h test/test_lib.h
test_test_rbtree_SOURCES = test/rbtree.c include/rbtree.h test/test_lib.h
test_test_vector_SOURCES = test/vector.c include/vector.h test/test_lib.h
test_test_vector_CFLAGS = -g -Wall -Wpedantic

AM_CFLAGS = -g -Wall -Wextra -Wpedantic
AM_CPPFLAGS = -I$(abs_top_srcdir)/include -I$(abs_top_srcdir)/test
TESTS = $(check_PROGRAMS)

include_HEADERS = include/heap.h include/heap_m.h include/list.h include/queue.h include/rbtree.h include/vector.h
# include/bst.h

.PHONY:	leakcheck
leakcheck:	$(TESTS)
	@for TEST in $^; do\
		valgrind --leak-check=full --log-file="$$TEST.log" $$TEST > /dev/null;\
		python3 tools/quiet.py "$$TEST.log";\
	done