check_PROGRAMS = heap heap_m list queue rbtree stack vector
# test/bst

bst_SOURCES = test/bst.c include/bst.h test/test_lib.h
heap_SOURCES = test/heap.c include/heap.h test/test_lib.h
heap_m_SOURCES = test/heap_m.c include/heap_m.h test/test_lib.h
list_SOURCES = test/list.c include/list.h test/test_lib.h
queue_SOURCES = test/queue.c include/queue.h test/test_lib.h
rbtree_SOURCES = test/rbtree.c include/rbtree.h test/test_lib.h
stack_SOURCES = test/stack.c include/stack.h test/test_lib.h
vector_SOURCES = test/vector.c include/vector.h test/test_lib.h

AM_CPPFLAGS = -I$(abs_top_srcdir)/include -I$(abs_top_srcdir)/test
TESTS = $(check_PROGRAMS)

.DUMMY:	asdf
asdf:
	echo $(abs_top_srcdir)/include
	ls $(abs_top_srcdir)/include
	echo "\n"
	echo $(abs_top_srcdir)/test
	ls $(abs_top_srcdir)/test

