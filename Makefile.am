check_PROGRAMS = \
	test/test_vector \
	test/test_list \
	test/test_slist \
	test/test_heap \
	test/test_deque \
	test/test_bst \
	test/test_rb \
	test/test_chash \
	test/test_namespace

test_test_namespace_SOURCES = test/namespace.c
test_test_chash_SOURCES = test/chash.c include/chash.h test/test_lib.h
test_test_slist_SOURCES = test/slist.c include/slist.h test/test_lib.h
test_test_rb_SOURCES = test/rb.c include/rb.h test/test_lib.h
test_test_bst_SOURCES = test/bst.c include/bst.h test/test_lib.h
test_test_deque_SOURCES = test/deque.c include/deque.h test/test_lib.h
test_test_heap_SOURCES = test/heap.c include/heap.h test/test_lib.h
test_test_list_SOURCES = test/list.c include/list.h test/test_lib.h
test_test_vector_SOURCES = test/vector.c include/vector.h test/test_lib.h
test_test_vector_CFLAGS = -g -Wall -Wpedantic -Werror
test_test_deque_CFLAGS = -g -Wall -Wpedantic -Werror
test_test_heap_CFLAGS = -g -Wall -Wpedantic -Werror
test_test_namespace_CFLAGS = -g -Wall -Wpedantic -Werror

AM_CFLAGS = -g -Wall -Wextra -Wpedantic -Werror
AM_CPPFLAGS = -I$(abs_top_srcdir)/include -I$(abs_top_srcdir)/test
TESTS = $(check_PROGRAMS)

include_HEADERS = \
	include/heap.h \
	include/list.h \
	include/rb.h \
	include/vector.h \
	include/deque.h \
	include/bst.h \
	include/slist.h \
	include/chash.h

.PHONY:	leakcheck
leakcheck:	$(TESTS)
	@for TEST in $^; do\
		valgrind --leak-check=full --log-file="$$TEST.log" $$TEST > /dev/null;\
		python3 tools/quiet.py "$$TEST.log";\
	done

.PHONY: namespace
namespace:
	@python3 tools/namespace.py > test/namespace.c
