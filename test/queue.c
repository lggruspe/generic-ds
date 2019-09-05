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
        char front = queue_peek(&queue);
        char *head = queue_peek_pointer(&queue);
        assert_true(front == array[i]);
        assert_true(head && *head == front);
        queue_dequeue(&queue);
    }
    assert_true(!queue_peek_pointer(&queue));
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
        const char *front = queue_peek(&queue);
        const char **ptr = queue_peek_pointer(&queue);
        assert_true(strcmp(front, array[i]) == 0);
        if (ptr) {
            assert_true(strcmp(*ptr, array[i]) == 0);
            assert_true(strcmp(*ptr, front) == 0);
        }
        queue_dequeue(&queue);
    }
    queue_destroy(&queue);
}

unit_test(test_queue_get_set)
{
    queue(int) queue = queue_create();
    assert_true(!queue_peek_pointer(&queue));
    assert_true(!queue_get_pointer(&queue, 0));
    for (int i = 0; i < 10; ++i) {
        queue_enqueue(&queue, i);
        queue_set(&queue, i, 2*i);
    }
    for (int i = 0; i < 10; ++i) {
        assert_true(queue_get(&queue, i) == 2*i);
        int *ptr = queue_get_pointer(&queue, i);
        assert_true(ptr && *ptr == 2*i);
    }
    queue_destroy(&queue);
    assert_true(!queue_peek_pointer(&queue));
    assert_true(!queue_get_pointer(&queue, 0));
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
    run_unit_test(test_queue_get_set);
    return exit_test();
}
