#include "builtin_core.h"
#include "cfunc.h"
#include "closure.h"
#include "cons.h"
#include "env.h"
#include "eval.h"
#include "macro.h"
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
    pobject p = cons_car(params);

    if (is_symbol(p)) {
        return env_define(env, 
                          cons_car(params), 
                          eval(env, cons_car(cons_cdr(params))));
    } else if (is_cons(p)) {
        return env_define(env,
                          cons_car(p),
                          closure_new(env, cons_cdr(p), cons_cdr(params)));
    }

    return NIL;
}

static pobject defmacro(pobject env, pobject params)
{
    pobject p = cons_car(params);

    if (is_cons(p)) {
        return env_define(env,
                          cons_car(p),
                          macro_new(env, cons_cdr(p), cons_cdr(params)));
    }

    return NIL;
}

static pobject builtin_macro_expand(pobject env, pobject params)
{
    pobject p = cons_car(params);

    if (is_cons(p)) {
        pobject macro = eval(env, cons_car(p));
        if (is_macro(macro))
            return macro_expand(env, macro, cons_cdr(p));
    }

    return NIL;
}

static pobject lambda(pobject env, pobject params)
{
    return closure_new(env, cons_car(params), cons_cdr(params));
}

static pobject macro(pobject env, pobject params)
{
    return macro_new(env, cons_car(params), cons_cdr(params));
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

static pobject builtin_print(pobject env, pobject params)
{
    pobject o = eval(env, cons_car(params));
    print(o);
    return NIL;
}

static pobject builtin_println(pobject env, pobject params)
{
    pobject o = eval(env, cons_car(params));
    println(o);
    return NIL;
}

void builtin_core_init(pobject *env)
{
    cons_assoc_set(env, symbol_intern("nil"),      NIL);
    cons_assoc_set(env, symbol_intern("#t"),       object_true);
    cons_assoc_set(env, symbol_intern("#f"),       NIL);
    cons_assoc_set(env, symbol_intern("quote"),    cfunc_new(quote));
    cons_assoc_set(env, symbol_intern("print"),    cfunc_new(builtin_print));
    cons_assoc_set(env, symbol_intern("println"),  cfunc_new(builtin_println));
    cons_assoc_set(env, symbol_intern("begin"),    cfunc_new(begin));
    cons_assoc_set(env, symbol_intern("cond"),     cfunc_new(cond));
    cons_assoc_set(env, symbol_intern("define"),   cfunc_new(define));
    cons_assoc_set(env, symbol_intern("defmacro"),     cfunc_new(defmacro));
    cons_assoc_set(env, symbol_intern("macro-expand"), cfunc_new(builtin_macro_expand));
    cons_assoc_set(env, symbol_intern("lambda"),   cfunc_new(lambda));
    cons_assoc_set(env, symbol_intern("macro"),    cfunc_new(macro));
    cons_assoc_set(env, symbol_intern("car"),      cfunc_new(car));
    cons_assoc_set(env, symbol_intern("cdr"),      cfunc_new(cdr));
    cons_assoc_set(env, symbol_intern("cons"),     cfunc_new(cons));
    cons_assoc_set(env, symbol_intern("="),        cfunc_new(equal));
    cons_assoc_set(env, symbol_intern(">"),        cfunc_new(gt));
}
