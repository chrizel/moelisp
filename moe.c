#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

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
    gc_collect(NIL);
    symbol_cleanup();
}

static void cleanup_signal_handler(int sig)
{
    cleanup();
    signal(sig, SIG_DFL);
    kill(getpid(), sig);
}

static void run()
{
    char *code;

    while ((code = input())) {
        pobject ast, result;
        ast = moe_read(code);
        result = eval(global_env, ast);

        printf(" --> ");
        println(result);
    }
}

int main(int argc, char *argv[])
{
    init();

    atexit(cleanup);
    signal(SIGINT, cleanup_signal_handler);
    signal(SIGKILL, cleanup_signal_handler);

    eval_file("startup.lisp");
    run();
    return 0;
}
