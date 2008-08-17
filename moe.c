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
    pobject env         = NIL;
    object_new_count    = 0;
    object_free_count   = 0;
    object_true         = symbol_intern("#t");

    builtin_core_init(&env);
    builtin_math_init(&env);

    printf("# env: ");
    println(env);

    if (argc > 1) {
        pobject ast;
        printf("# input string: %s\n", argv[1]);

        ast = read(argv[1]);
        printf("# parsed ast: ");
        println(ast);

        printf("# evaluated result: ");
        println(eval(env, ast));
    }

    printf("# object_new_count = %d\n", object_new_count);
    printf("# object_free_count = %d\n", object_free_count);
    printf("# leaked objects = %d\n", object_new_count - object_free_count);
    
    return 0;
}
