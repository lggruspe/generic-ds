#include "queue.h"
#include "test_lib.h"
#include <stdbool.h>
#include <string.h>

#define test_queue_setup(type) bool passed = true;\
queue(type) queue;\
queue_init(queue)

#define test_queue_teardown() queue_destroy(queue); return passed

bool test_queue_init()
{
    test_queue_setup(char);
    check_assertion(!queue.array);
    check_assertion(queue.size == 0);
    check_assertion(queue.capacity == 0);
    check_assertion(queue.front == 0);
    check_assertion(queue.back == 0);
    test_queue_teardown();
}

bool test_queue_is_empty()
{
    test_queue_setup(char);
    check_assertion(queue_is_empty(queue));
    queue_enqueue(queue, 0);
    check_assertion(!queue_is_empty(queue));
    queue_dequeue(queue);
    check_assertion(queue_is_empty(queue));
    test_queue_teardown();
}

bool test_queue_is_full()
{
    test_queue_setup(char);
    check_assertion(queue_is_full(queue));
    queue_enqueue(queue, 1);
    check_assertion(queue_is_full(queue));
    queue_enqueue(queue, 2);
    check_assertion(queue_is_full(queue));
    queue_enqueue(queue, 3);
    check_assertion(!queue_is_full(queue));
    queue_enqueue(queue, 4);
    check_assertion(queue_is_full(queue));
    test_queue_teardown();
}

bool test_queue_increase_capacity()
{
    test_queue_setup(char);
    queue_increase_capacity(queue);
    check_assertion(queue.capacity == 1);
    for (size_t i = 0; i < 3; ++i) {
        queue_increase_capacity(queue);
    }
    check_assertion(queue.capacity == 8);
    test_queue_teardown();
}

bool test_queue_enqueue()
{
    test_queue_setup(char);
    for (char c = '0'; c <= '9'; ++c) {
        queue_enqueue(queue, c);
    }
    check_assertion(queue.size == 10);
    test_queue_teardown();
}

bool test_queue_dequeue()
{
    test_queue_setup(char);
    for (char c = '0'; c <= '9'; ++c) {
        queue_enqueue(queue, c);
    }
    for (size_t i = 0; i < 10; ++i) {
        queue_dequeue(queue);
    }
    check_assertion(queue_is_empty(queue));
    queue_dequeue(queue);
    check_assertion(queue_is_empty(queue));
    test_queue_teardown();
}

bool test_queue_peek()
{
    test_queue_setup(char);
    char array[] = "0123456789";
    for (size_t i = 0; i < 10; ++i) {
        queue_enqueue(queue, array[i]);
    }
    for (size_t i = 0; i < 10; ++i) {
        check_assertion(array[i] == *(queue_peek(queue)));
        queue_dequeue(queue);
    }
    void *ptr = queue_peek(queue);
    check_assertion(!ptr);
    test_queue_teardown();
}

bool test_queue_destroy()
{
    test_queue_setup(char);
    for (char c = '0'; c <= '9'; ++c) {
        queue_enqueue(queue, c);
    }
    queue_destroy(queue);
    check_assertion(!queue.array);
    check_assertion(queue.size == 0);
    check_assertion(queue.capacity == 0);
    check_assertion(queue.front == 0);
    check_assertion(queue.back == 0);
    test_queue_teardown();
}

bool test_queue_pointer_type()
{
    test_queue_setup(const char*);
    queue_enqueue(queue, "hello");
    queue_enqueue(queue, ", ");
    queue_enqueue(queue, "world");
    queue_enqueue(queue, "!\n");

    const char *array[] = {"hello", ", ", "world", "!\n"};
    for (size_t i = 0; i < 4; ++i) {
        const char **ptr = queue_peek(queue);
        queue_dequeue(queue);
        check_assertion(ptr);
        if (ptr) {
            check_assertion(strcmp(*ptr, array[i]) == 0);
        }
    }
    test_queue_teardown();
}

int main()
{
    run_test(test_queue_init);
    run_test(test_queue_is_empty);
    run_test(test_queue_is_full);
    run_test(test_queue_increase_capacity);
    run_test(test_queue_peek);
    run_test(test_queue_enqueue);
    run_test(test_queue_dequeue);
    return exit_test();
}
