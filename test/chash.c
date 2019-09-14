#include "chash.h"
#include "test_lib.h"
#include <string.h>

chash_register(hi, int, 100)
chash_register(hs, const char *, 50)

int identity_hash(int i)
{
    return i;
}

int string_hash(const char *s)
{
    int hash = 0;
    for (const char *pc = s; *pc; ++pc) {
        hash = (hash << 7) + *s;
    }
    return hash;
}

unit_test(test_chash_string)
{
    const char *array[] = { "a", "aa", "aaa", "b", "bb", "bbb", "c", "cc", "ccc", "a", "b", "c" };
    chash(hs) set = chash_create(hs, string_hash, .compare = strcmp);

    chash_chain(hs) node = chash_search(hs, set, "a");
    assert_true(!node);

    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i < 12; ++i) {
            set = chash_insert(hs, set, array[i]);
        }
    }

    assert_true(set.size == 9);
    for (int i = 0; i < 12; ++i) {
        chash_chain(hs) node = chash_search(hs, set, array[i]);
        assert_true(node && strcmp(node->data, array[i]) == 0);
    }

    set = chash_delete(hs, set, "a");
    assert_true(set.size == 8);

    node = chash_search(hs, set, "a");
    assert_true(!node);
    for (int i = 1; i < 12; ++i) {
        if (i == 9) {
            continue;
        }
        chash_chain(hs) node = chash_search(hs, set, array[i]);
        assert_true(node && strcmp(node->data, array[i]) == 0);
    }

    int Bucket_size = 50;
    set = chash_destroy(hs, set);
    for (int i = 0; i < Bucket_size; ++i) {
        assert_true(!(set.array[i]));
    }
    assert_true(set.size == 0);
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
    run_unit_test(test_chash_string);
    return exit_test();
}
