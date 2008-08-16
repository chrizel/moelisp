#include "builtin_core.h"
#include "cfunc.h"
#include "cons.h"
#include "eval.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "symbol.h"

static pobject begin(pobject env, pobject params)
{
    pobject result = NIL;

    while (is_cons(params)) {
        result = eval(env, cons_car(params));
        params = cons_cdr(params);
    }

    return result;
}

static pobject cond(pobject env, pobject params)
{
    return NIL; /* TODO */
}

static pobject equal(pobject env, pobject params)
{
    pobject o1 = eval(env, cons_car(params));
    pobject o2 = eval(env, cons_car(cons_cdr(params)));
    return object_equal(o1, o2) ? object_true : NIL;
}

void builtin_core_init(pobject *env)
{
    cons_assoc_set(env, symbol_intern("nil"),   NIL);
    cons_assoc_set(env, symbol_intern("#t"),    object_true);
    cons_assoc_set(env, symbol_intern("#f"),    NIL);
    cons_assoc_set(env, symbol_intern("begin"), cfunc_new(begin));
    cons_assoc_set(env, symbol_intern("cond"),  cfunc_new(cond));
    cons_assoc_set(env, symbol_intern("="),     cfunc_new(equal));
}
