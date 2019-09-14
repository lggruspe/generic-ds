#include "bst.h"
#include "deque.h"
#include "heap.h"
#include "list.h"
#include "rb.h"
#include "vector.h"
#include "slist.h"
#include "chash.h"

bst_register(bst, const char *)
deque_register(deque, const char *)
heap_register(heap, const char *)
list_register(list, const char *)
rb_register(rb, const char *)
vector_register(vector, const char *)
slist_register(slist, const char *)
chash_register(chash, const char *, 1)

bst_register(ns1, const char *)
deque_register(ns1, const char *)
heap_register(ns1, const char *)
list_register(ns1, const char *)
//vector_register(ns1, const char *)
slist_register(ns1, const char *)

deque_register(ns2, const char *)
heap_register(ns2, const char *)
list_register(ns2, const char *)
rb_register(ns2, const char *)
//vector_register(ns2, const char *)
slist_register(ns2, const char *)

int main()
{
}
