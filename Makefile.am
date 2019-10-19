check_PROGRAMS = \
	test/test_vector \
	test/test_list \
	test/test_slist \
	test/test_heap \
	test/test_deque \
	test/test_bst \
	test/test_rb \
	test/test_chash \
	test/test_ohash \
	test/test_namespace

test_test_namespace_SOURCES = test/namespace.c
test_test_chash_SOURCES = test/chash.c include/lggds/chash.h test/test_lib.h
test_test_ohash_SOURCES = test/ohash.c include/lggds/ohash.h test/test_lib.h
test_test_slist_SOURCES = test/slist.c include/lggds/slist.h test/test_lib.h
test_test_rb_SOURCES = test/rb.c include/lggds/rb.h test/test_lib.h
test_test_bst_SOURCES = test/bst.c include/lggds/bst.h test/test_lib.h
test_test_deque_SOURCES = test/deque.c include/lggds/deque.h test/test_lib.h
test_test_heap_SOURCES = test/heap.c include/lggds/heap.h test/test_lib.h
test_test_list_SOURCES = test/list.c include/lggds/list.h test/test_lib.h
test_test_vector_SOURCES = test/vector.c include/lggds/vector.h test/test_lib.h
test_test_vector_CFLAGS = -g -Wall -Wpedantic -Werror
test_test_deque_CFLAGS = -g -Wall -Wpedantic -Werror
test_test_heap_CFLAGS = -g -Wall -Wpedantic -Werror
test_test_namespace_CFLAGS = -g -Wall -Wpedantic -Werror

AM_CFLAGS = -g -Wall -Wextra -Wpedantic -Werror
AM_CPPFLAGS = -I$(abs_top_srcdir)/include/lggds -I$(abs_top_srcdir)/test
TESTS = $(check_PROGRAMS)

pkginclude_HEADERS = \
	include/lggds/heap.h \
	include/lggds/list.h \
	include/lggds/rb.h \
	include/lggds/vector.h \
	include/lggds/deque.h \
	include/lggds/bst.h \
	include/lggds/slist.h \
	include/lggds/chash.h \
	include/lggds/ohash.h

.PHONY:	leakcheck
leakcheck:	$(TESTS)
	@for TEST in $^; do\
		valgrind --leak-check=full --log-file="$$TEST.log" $$TEST > /dev/null;\
		python3 $(abs_top_srcdir)/tools/quiet.py "$$TEST.log";\
	done

.PHONY: namespace
namespace:
	@python3 $(abs_top_srcdir)/tools/namespace.py > $(abs_top_srcdir)/test/namespace.c
