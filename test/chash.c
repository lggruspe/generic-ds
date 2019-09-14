#include "chash.h"
#include "test_lib.h"

chash_register(hi, int, 100)
chash_register(hs, const char *, 50)

int identity_hash(int i)
{
    return i;
}

unit_test(test_chash_set)
{
    chash(hi) set = chash_create(hi, identity_hash);

    chash_chain(hi) node = chash_search(hi, set, 0);
    assert_true(!node);

    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i < 10; ++i) {
            set = chash_insert(hi, set, i);
        }
    }

    assert_true(set.size == 10);
    for (int i = 0; i < 10; ++i) {
        chash_chain(hi) node = chash_search(hi, set, i);
        assert_true(node && node->data == i);
    }
    set = chash_delete(hi, set, 0);
    assert_true(set.size == 9);
    node = chash_search(hi, set, 0);
    assert_true(!node);
    for (int i = 1; i < 10; ++i) {
        chash_chain(hi) node = chash_search(hi, set, i);
        assert_true(node && node->data == i);
    }

    int Bucket_size = 100;
    set = chash_destroy(hi, set);
    for (int i = 0; i < Bucket_size; ++i) {
        assert_true(!(set.array[i]));
    }
    assert_true(set.size == 0);
}

int main()
{
    run_unit_test(test_chash_set);
    return exit_test();
}
