#include <stdio.h>

#include "cons.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "read.h"
#include "symbol.h"

int main(int argc, char *argv[])
{
    pobject o1 = symbol_intern("foo");
    pobject o2 = symbol_intern("bar");
    pobject o3 = symbol_intern("foo");

    printf("o1: %p\n", o1);
    printf("o2: %p\n", o2);
    printf("o3: %p\n", o3);

    return 0;
}
