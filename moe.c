#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfunc.h"
#include "cons.h"
#include "eval.h"
#include "gc.h"
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

static pobject eval_file(char *filename)
{
    pobject ast, result;
    long size;
    char *buf;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);

        buf = malloc(size + 9);
        memcpy(buf, "(begin ", 7);
        rewind(fp);
        size = fread(buf + 7, sizeof(char), size, fp);
        buf[size+7] = ')';
        buf[size+8] = '\0';

        ast = moe_read(buf);

        result = eval(global_env, ast);
        free(buf);

        return result;
    }

    return NIL;
}

static void init()
{
    object_new_count    = 0;
    object_free_count   = 0;
    object_true         = symbol_intern("#t");
    symbol_parent_env   = symbol_intern("__parent_env__");

    builtin_core_init(&global_env);
    builtin_math_init(&global_env);
}

static void cleanup()
{
    printf("\n\nBefore gc_collect:\n* object_new_count = %d\n", object_new_count);
    printf("* object_free_count = %d\n", object_free_count);
    printf("* leaked objects = %d\n", object_new_count - object_free_count);

    gc_collect(NIL);

    printf("\n\nAfter gc_collect:\n* object_new_count = %d\n", object_new_count);
    printf("* object_free_count = %d\n", object_free_count);
    printf("* leaked objects = %d\n", object_new_count - object_free_count);

    symbol_cleanup();

    printf("\n\nAfter symbol_cleanup:\n* object_new_count = %d\n", object_new_count);
    printf("* object_free_count = %d\n", object_free_count);
    printf("* leaked objects = %d\n", object_new_count - object_free_count);
}

static void run()
{
    char *code;

/*
    printf("* global_env: ");
    println(global_env);
*/
    while ((code = input())) {
        pobject ast, result;
        /*
        printf("* input string: %s", code);
        */

        ast = moe_read(code);
        /*
        printf("* parsed ast: ");
        println(ast);
        */

        result = eval(global_env, ast);

        printf("\n --> ");
        println(result);
    }
}

int main(int argc, char *argv[])
{
    init();
    atexit(cleanup);
    eval_file("startup.lisp");
    run();
    return 0;
}
