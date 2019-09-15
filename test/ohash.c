#include "ohash.h"
#include "test_lib.h"
#include <string.h>

ohash_register(hi, int, 100)
ohash_register(hs, const char *, 50)

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

unit_test(test_ohash_string)
{
    const char *array[] = { "a", "aa", "aaa", "b", "bb", "bbb", "c", "cc", "ccc", "a", "b", "c" };
    ohash(hs) set = ohash_create(hs, string_hash, .compare = strcmp);

    int index = ohash_search(hs, set, "a");
    assert_true(index == -1);

    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i < 12; ++i) {
            set = ohash_insert(hs, set, array[i]);
        }
    }

    assert_true(set.size == 9);
    for (int i = 0; i < 12; ++i) {
        int index = ohash_search(hs, set, array[i]);
        assert_true(index != -1 && strcmp(set.array[index].data, array[i]) == 0);
    }

    set = ohash_delete(hs, set, "a");
    assert_true(set.size == 8);

    index = ohash_search(hs, set, "a");
    assert_true(index == -1);
    for (int i = 1; i < 12; ++i) {
        if (i == 9) {
            continue;
        }
        int index = ohash_search(hs, set, array[i]);
        assert_true(index != -1 && strcmp(set.array[index].data, array[i]) == 0);
    }

    set = ohash_destroy(hs, set);
    assert_true(!set.array);
    assert_true(set.size == 0);
}

unit_test(test_ohash_set)
{
    ohash(hi) set = ohash_create(hi, identity_hash);

    int index = ohash_search(hi, set, 0);
    assert_true(index == -1);

    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i < 10; ++i) {
            set = ohash_insert(hi, set, i);
        }
    }

    assert_true(set.size == 10);
    for (int i = 0; i < 10; ++i) {
        int index = ohash_search(hi, set, i);
        assert_true(index != -1 && set.array[index].data == i);
    }

    set = ohash_delete(hi, set, 0);
    assert_true(set.size == 9);

    index = ohash_search(hi, set, 0);
    assert_true(index == -1);

    for (int i = 1; i < 10; ++i) {
        int index = ohash_search(hi, set, i);
        assert_true(index != -1 && set.array[index].data == i);
    }

    set = ohash_destroy(hi, set);
    assert_true(!set.array);
    assert_true(set.size == 0);
}

int main()
{
    run_unit_test(test_ohash_set);
    run_unit_test(test_ohash_string);
    return exit_test();
}
