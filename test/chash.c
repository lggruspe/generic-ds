#include "chash.h"
#include "test_lib.h"

chash_register(set, int, 100)

unit_test(test_chash_set)
{
    chash(set) set = chash_create(set);

    chash_chain(set) node = chash_search(set, set, 0);
    assert_true(!node);

    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i < 10; ++i) {
            set = chash_insert(set, set, i);
        }
    }

    assert_true(set.size == 10);
    for (int i = 0; i < 10; ++i) {
        chash_chain(set) node = chash_search(set, set, i);
        assert_true(node && node->data == i);
    }
    set = chash_delete(set, set, 0);
    assert_true(set.size == 9);
    node = chash_search(set, set, 0);
    assert_true(!node);
    for (int i = 1; i < 10; ++i) {
        chash_chain(set) node = chash_search(set, set, i);
        assert_true(node && node->data == i);
    }

    int Bucket_size = 100;
    set = chash_destroy(set, set);
    for (int i = 0; i < Bucket_size; ++i) {
        assert_true(!(set.array[i]));
    }
    assert_true(set.size == 0);
    assert_true(!(set.hash));
    assert_true(!(set.compare));
}

int main()
{
    run_unit_test(test_chash_set);
    return exit_test();
}
