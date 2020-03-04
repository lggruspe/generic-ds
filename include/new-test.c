#include "new/bst.h"
#include "new/chash.h"
#include "new/deque.h"
#include "new/list.h"
#include "new/ohash.h"
#include "new/pair.h"
#include "new/pqueue.h"
#include "new/rb.h"
#include "new/vector.h"
#include <stdbool.h>
#include <stdio.h>

static inline bool lessthan(int a, int b)
{
    return a < b;
}

static inline int hash(int n)
{
    return n;
}

static inline bool equal(int a, int b)
{
    return a == b;
}

BST_GENERATE(bst, int, lessthan)
CHASH_GENERATE(chash, int, hash, 11, equal)
DEQUE_GENERATE(deque, int)
LIST_GENERATE(list, int)
OHASH_GENERATE(ohash, int, hash, 11, equal);
PAIR_GENERATE(pair, int, char*)
PQUEUE_GENERATE(pqueue, int, lessthan)
RB_GENERATE(rb, int, lessthan)
VECTOR_GENERATE(vector, int)

void run_bst()
{
    bst_node *t = NULL;
    for (int i = 0; i < 10; ++i) {
        t = bst_insert(t, bst_new(i));
    }
    bst_node *n = bst_minimum(t);
    while (n) {
        printf("%d ", bst_get(n));
        n = bst_next(n);
    }
    printf("\n");
    bst_destroy(t);
}

void run_chash()
{
    chash_type m = chash_create();
    for (int i = 0; i < 35; ++i) {
        chash_insert(&m, i);
    }
    for (int i = 0; i < 35; ++i) {
        chash_node *n = chash_search(&m, i);
        printf("(%d)\n", chash_get(n));
        chash_delete(&m, i);
    }
    for (int i = 0; i < 35; ++i) {
        chash_node *n = chash_search(&m, i);
        if (n) {
            printf("(error)\n");
        }
    }
    chash_destroy(&m);
}

void run_deque()
{
    deque_type q = deque_create();
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            deque_push_front(&q, i);
        } else {
            deque_push(&q, i);
        }
    }
    for (int i = 0; i < deque_size(&q); ++i) {
        printf("%d ", deque_get(&q, i));
    }
    printf("\n");
    deque_destroy(&q);
}

void run_list()
{
    list_node *l = NULL;
    for (int i = 0; i < 10; ++i) {
        l = list_append(l, list_new(i));
    }
    list_node *n = l;
    do {
        printf("%d ", list_get(n));
        n = n->next;
    } while (n != l);
    printf("\n");
    list_destroy(n->next);
}

void run_ohash()
{
    ohash_type m = ohash_create();
    for (int i = 0; i < 35; ++i) {
        ohash_insert(&m, i);
    }
    for (int i = 0; i < 35; ++i) {
        int k = ohash_search(&m, i);
        if (ohash_is_valid(&m, k)) {
            printf("(%d)\n", ohash_get(&m, k));
            ohash_delete(&m, i);
        }
    }
    for (int i = 0; i < 35; ++i) {
        int k = ohash_search(&m, i);
        if (k != -1) {
            printf("(error)\n");
        }
    }
    ohash_destroy(&m);
}

void run_pair()
{
    pair_type ps[] = {
        pair_make(1, "hello"),
        pair_make(2, ","),
        pair_make(3, " "),
        pair_make(4, "world"),
        pair_make(5, "!"),
        pair_make(6, "\n"),
    };
    for (int i = 0; i < 6; ++i) {
        printf("%d %d %s\n", i, ps[i].first, ps[i].second);
    }
}

void run_pqueue()
{
    pqueue_type q = pqueue_create();
    for (int i = 9; i >= 0; --i) {
        pqueue_insert(&q, i);
    }
    while (!pqueue_is_empty(&q)) {
        printf("%d\n", pqueue_pop_front(&q));
    }
    pqueue_destroy(&q);
}

void run_rb()
{
    rb_node *t = NULL;
    for (int i = 0; i < 10; ++i) {
        t = rb_insert(t, rb_new(i));
    }
    rb_node *n = rb_minimum(t);
    while (n) {
        printf("%d ", rb_get(n));
        n = rb_next(n);
    }
    printf("\n");
    rb_destroy(t);
}

void run_vector()
{
    vector_type v = vector_create();
    for (int i = 0; i < 10; ++i) {
        vector_push(&v, i);
    }
    while (!vector_is_empty(&v)) {
        printf("%d ", vector_pop(&v));
    }
    printf("\n");
    vector_destroy(&v);
}

#include "new/algorithms/sort/heapsort.h"
#include <time.h>
#include <stdlib.h>

HEAPSORT_GENERATE(heap, int, lessthan)

void run_heap_sort()
{
    srand(time(NULL));
    int n = 10;
    int array[n];
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 10;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    heap_sort(array, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
    run_bst();
    run_chash();
    run_deque();
    run_list();
    run_ohash();
    run_pair();
    run_pqueue();
    run_rb();
    run_vector();

    run_heap_sort();
}
