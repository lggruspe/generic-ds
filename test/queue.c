#include "queue.h"
#include "test_lib.h"
#include <string.h>

unit_test(test_queue_init)
{
    queue(char) queue = queue_create();
    assert_true(!queue.array);
    assert_true(queue.size == 0);
    assert_true(queue.capacity == 0);
    assert_true(queue.front == 0);
    assert_true(queue.back == 0);
    queue_destroy(&queue);
}

unit_test(test_queue_is_empty)
{
    queue(char) queue = queue_create();
    assert_true(queue_is_empty(&queue));
    queue_enqueue(&queue, 0);
    assert_true(!queue_is_empty(&queue));
    queue_dequeue(&queue);
    assert_true(queue_is_empty(&queue));
    queue_destroy(&queue);
}

unit_test(test_queue_is_full)
{
    queue(char) queue = queue_create();
    assert_true(queue_is_full(&queue));
    queue_enqueue(&queue, 1);
    assert_true(queue_is_full(&queue));
    queue_enqueue(&queue, 2);
    assert_true(queue_is_full(&queue));
    queue_enqueue(&queue, 3);
    assert_true(!queue_is_full(&queue));
    queue_enqueue(&queue, 4);
    assert_true(queue_is_full(&queue));
    queue_destroy(&queue);
}

unit_test(test_queue_increase_capacity)
{
    queue(char) queue = queue_create();
    queue_increase_capacity(&queue);
    assert_true(queue.capacity == 1);
    for (int i = 0; i < 3; ++i) {
        queue_increase_capacity(&queue);
    }
    assert_true(queue.capacity == 8);
    queue_destroy(&queue);
}

unit_test(test_queue_enqueue)
{
    queue(char) queue = queue_create();
    for (char c = '0'; c <= '9'; ++c) {
        queue_enqueue(&queue, c);
    }
    assert_true(queue.size == 10);
    queue_destroy(&queue);
}

unit_test(test_queue_dequeue)
{
    queue(char) queue = queue_create();
    for (char c = '0'; c <= '9'; ++c) {
        queue_enqueue(&queue, c);
    }
    for (int i = 0; i < 10; ++i) {
        queue_dequeue(&queue);
    }
    assert_true(queue_is_empty(&queue));
    queue_dequeue(&queue);
    assert_true(queue_is_empty(&queue));
    queue_destroy(&queue);
}

unit_test(test_queue_peek)
{
    queue(char) queue = queue_create();
    char array[] = "0123456789";
    for (int i = 0; i < 10; ++i) {
        queue_enqueue(&queue, array[i]);
    }
    for (int i = 0; i < 10; ++i) {
        assert_true(array[i] == *(queue_peek(&queue)));
        queue_dequeue(&queue);
    }
    void *ptr = queue_peek(&queue);
    assert_true(!ptr);
    queue_destroy(&queue);
}

unit_test(test_queue_destroy)
{
    queue(char) queue = queue_create();
    for (char c = '0'; c <= '9'; ++c) {
        queue_enqueue(&queue, c);
    }
    queue_destroy(&queue);
    assert_true(!queue.array);
    assert_true(queue.size == 0);
    assert_true(queue.capacity == 0);
    assert_true(queue.front == 0);
    assert_true(queue.back == 0);
    queue_destroy(&queue);
}

unit_test(test_queue_pointer_type)
{
    queue(const char*) queue = queue_create();
    queue_enqueue(&queue, "hello");
    queue_enqueue(&queue, ", ");
    queue_enqueue(&queue, "world");
    queue_enqueue(&queue, "!\n");

    const char *array[] = {"hello", ", ", "world", "!\n"};
    for (int i = 0; i < 4; ++i) {
        const char **ptr = queue_peek(&queue);
        queue_dequeue(&queue);
        assert_true(ptr);
        if (ptr) {
            assert_true(strcmp(*ptr, array[i]) == 0);
        }
    }
    queue_destroy(&queue);
}

int main()
{
    run_unit_test(test_queue_init);
    run_unit_test(test_queue_is_empty);
    run_unit_test(test_queue_is_full);
    run_unit_test(test_queue_increase_capacity);
    run_unit_test(test_queue_peek);
    run_unit_test(test_queue_enqueue);
    run_unit_test(test_queue_dequeue);
    return exit_test();
}
