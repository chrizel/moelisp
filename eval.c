#include <stdio.h>

#include "closure.h"
#include "cons.h"
#include "env.h"
#include "gc.h"
#include "macro.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "symbol.h"

pobject eval_apply(pobject env, pobject proc, pobject params)
{
    if (!(is_nil(params) || is_cons(params)))
        params = gc_add( cons_new(params, NIL) );

    /*
    printf("* ");
    print(proc);
    printf(": ");
    println(params);
    */

    if (is_cfunc(proc))
        return proc->data.cfunc(env, params);
    else if (is_closure(proc))
        return closure_eval(env, proc, params);
    else if (is_macro(proc))
        return macro_eval(env, proc, params);
    else
        return NIL;
}

pobject eval(pobject env, pobject code)
{
    if (is_cons(code))
        return eval_apply(env, eval(env, cons_car(code)), cons_cdr(code));
    else if (is_symbol(code))
        return cons_car(env_lookup(env, code));
    else
        return code;
    return NIL;
}
