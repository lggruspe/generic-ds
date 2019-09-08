#include "rb.h"
#include "test_lib.h"

rb_register(ri, int)
rb_register(rs, const char *)

int main()
{
    return exit_test();
}
