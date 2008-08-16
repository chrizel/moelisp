#include <stdio.h>

#include "cfunc.h"
#include "cons.h"
#include "eval.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "read.h"
#include "symbol.h"

#include "builtin_core.h"
#include "builtin_math.h"

int main(int argc, char *argv[])
{
    pobject env = NIL;

    builtin_core_init(&env);
    builtin_math_init(&env);

    if (argc > 1)
        println(eval(env, read(argv[1])));
    
    return 0;
}
