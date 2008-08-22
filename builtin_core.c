#include "builtin_core.h"
#include "cfunc.h"
#include "closure.h"
#include "cons.h"
#include "env.h"
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

static pobject define(pobject env, pobject params)
{
    return env_define(env, 
                      cons_car(params), 
                      eval(env, cons_car(cons_cdr(params))));
}

static pobject lambda(pobject env, pobject params)
{
    return closure_new(env, cons_car(params), cons_cdr(params));
}

static pobject car(pobject env, pobject params)
{
    return cons_car(eval(env, cons_car(params)));
}

static pobject cdr(pobject env, pobject params)
{
    return cons_cdr(eval(env, cons_car(params)));
}

static pobject cons(pobject env, pobject params)
{
    pobject o1 = eval(env, cons_car(params));
    pobject o2 = eval(env, cons_car(cons_cdr(params)));
    return cons_new(o1, o2);
}

void builtin_core_init(pobject *env)
{
    cons_assoc_set(env, symbol_intern("nil"),    NIL);
    cons_assoc_set(env, symbol_intern("#t"),     object_true);
    cons_assoc_set(env, symbol_intern("#f"),     NIL);
    cons_assoc_set(env, symbol_intern("quote"),  cfunc_new(quote));
    cons_assoc_set(env, symbol_intern("begin"),  cfunc_new(begin));
    cons_assoc_set(env, symbol_intern("cond"),   cfunc_new(cond));
    cons_assoc_set(env, symbol_intern("define"), cfunc_new(define));
    cons_assoc_set(env, symbol_intern("lambda"), cfunc_new(lambda));
    cons_assoc_set(env, symbol_intern("car"),    cfunc_new(car));
    cons_assoc_set(env, symbol_intern("cdr"),    cfunc_new(cdr));
    cons_assoc_set(env, symbol_intern("cons"),   cfunc_new(cons));
    cons_assoc_set(env, symbol_intern("="),      cfunc_new(equal));
    cons_assoc_set(env, symbol_intern(">"),      cfunc_new(gt));
}
