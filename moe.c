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

static pobject global_env = NIL;

static char * input()
{
    static char buf[1024];
    printf("\n> ");
    fflush(stdout);
    return fgets(buf, 1024, stdin);
}

static void init()
{
    object_new_count    = 0;
    object_free_count   = 0;
    object_true         = symbol_intern("#t");

    builtin_core_init(&global_env);
    builtin_math_init(&global_env);
}

static void cleanup()
{
    printf("\n\n* object_new_count = %d\n", object_new_count);
    printf("* object_free_count = %d\n", object_free_count);
    printf("* leaked objects = %d\n\n", object_new_count - object_free_count);
}

static void run()
{
    char *code;

    printf("* global_env: ");
    println(global_env);
    while ((code = input())) {
        pobject ast;
        printf("* input string: %s", code);

        ast = moe_read(code);
        printf("* parsed ast: ");
        println(ast);

        printf(" --> ");
        println(eval(global_env, ast));
    }
}

int main(int argc, char *argv[])
{
    init();
    run();
    cleanup();
    return 0;
}
