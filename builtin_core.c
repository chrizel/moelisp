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
    while (is_cons(params)) {
        pobject entry = cons_car(params);
        if (is_cons(entry)) {
            if (eval(env, cons_car(entry)))
                return eval(env, object_prepend_begin( cons_cdr( entry ) ) );
        } else {
            return eval(env, entry);
        }
        params = cons_cdr(params);
    }

    return NIL;
}

static pobject equal(pobject env, pobject params)
{
    pobject o1 = eval(env, cons_car(params));
    pobject o2 = eval(env, cons_car(cons_cdr(params)));
    return object_bool(object_equal(o1, o2));
}

static pobject gt(pobject env, pobject params)
{
    pobject o1 = eval(env, cons_car(params));
    pobject o2 = eval(env, cons_car(cons_cdr(params)));
    return object_bool(is_number(o1) 
                    && is_number(o2) 
                    && number_value(o1) > number_value(o2));
}

static pobject quote(pobject env, pobject params)
{
    return cons_car(params);
}

void builtin_core_init(pobject *env)
{
    cons_assoc_set(env, symbol_intern("nil"),   NIL);
    cons_assoc_set(env, symbol_intern("#t"),    object_true);
    cons_assoc_set(env, symbol_intern("#f"),    NIL);
    cons_assoc_set(env, symbol_intern("quote"), cfunc_new(quote));
    cons_assoc_set(env, symbol_intern("begin"), cfunc_new(begin));
    cons_assoc_set(env, symbol_intern("cond"),  cfunc_new(cond));
    cons_assoc_set(env, symbol_intern("="),     cfunc_new(equal));
    cons_assoc_set(env, symbol_intern(">"),     cfunc_new(gt));
}
