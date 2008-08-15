#include <stdio.h>

#include "cons.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "read.h"
#include "symbol.h"

int main(int argc, char *argv[])
{
    println(read("(+ 1 2 3)"));
    return 0;
}
