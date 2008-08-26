#include "builtin_core.h"
#include "cfunc.h"
#include "closure.h"
#include "cons.h"
#include "env.h"
#include "eval.h"
#include "gc.h"
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
                          gc_add(closure_new(env, cons_cdr(p), cons_cdr(params))));
    }

    return NIL;
}

static pobject set(pobject env, pobject params)
{
    pobject symbol = cons_car(params);
    if (is_symbol(symbol)) {
        pobject value = eval(env, cons_nth(params, 2));
        pobject cons  = env_lookup(env, symbol);
        if (is_cons(cons)) {
            cons_car_set(cons, value);
            return value;
        }
    }

    return NIL;
}

static pobject defmacro(pobject env, pobject params)
{
    pobject p = cons_car(params);

    if (is_cons(p)) {
        return env_define(env,
                          cons_car(p),
                          gc_add(macro_new(env, cons_cdr(p), cons_cdr(params))));
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
    return gc_add(closure_new(env, cons_car(params), cons_cdr(params)));
}

static pobject macro(pobject env, pobject params)
{
    return gc_add(macro_new(env, cons_car(params), cons_cdr(params)));
}

static pobject apply(pobject env, pobject params)
{
    /* XXX: apply needs more work */
    return eval_apply(env, eval(env, cons_car(params)), 
                      eval(env, cons_nth(params, 2)));
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
    return gc_add(cons_new(o1, o2));
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

static pobject collect(pobject env, pobject params)
{
    gc_collect(env);
    return NIL;
}

void builtin_core_init(pobject *env)
{
    cons_assoc_set(env, symbol_intern("nil"),      NIL, 1);
    cons_assoc_set(env, symbol_intern("#t"),       object_true, 1);
    cons_assoc_set(env, symbol_intern("#f"),       NIL, 1);
    cons_assoc_set(env, symbol_intern("quote"),    gc_add(cfunc_new(quote)), 1);
    cons_assoc_set(env, symbol_intern("print"),    gc_add(cfunc_new(builtin_print)), 1);
    cons_assoc_set(env, symbol_intern("println"),  gc_add(cfunc_new(builtin_println)), 1);
    cons_assoc_set(env, symbol_intern("begin"),    gc_add(cfunc_new(begin)), 1);
    cons_assoc_set(env, symbol_intern("cond"),     gc_add(cfunc_new(cond)), 1);
    cons_assoc_set(env, symbol_intern("set!"),     gc_add(cfunc_new(set)), 1);
    cons_assoc_set(env, symbol_intern("define"),   gc_add(cfunc_new(define)), 1);
    cons_assoc_set(env, symbol_intern("defmacro"),     gc_add(cfunc_new(defmacro)), 1);
    cons_assoc_set(env, symbol_intern("macro-expand"), gc_add(cfunc_new(builtin_macro_expand)), 1);
    cons_assoc_set(env, symbol_intern("lambda"),   gc_add(cfunc_new(lambda)), 1);
    cons_assoc_set(env, symbol_intern("macro"),    gc_add(cfunc_new(macro)), 1);
    cons_assoc_set(env, symbol_intern("apply"),    gc_add(cfunc_new(apply)), 1);
    cons_assoc_set(env, symbol_intern("car"),      gc_add(cfunc_new(car)), 1);
    cons_assoc_set(env, symbol_intern("cdr"),      gc_add(cfunc_new(cdr)), 1);
    cons_assoc_set(env, symbol_intern("cons"),     gc_add(cfunc_new(cons)), 1);
    cons_assoc_set(env, symbol_intern("collect"),  gc_add(cfunc_new(collect)), 1);
    cons_assoc_set(env, symbol_intern("="),        gc_add(cfunc_new(equal)), 1);
    cons_assoc_set(env, symbol_intern(">"),        gc_add(cfunc_new(gt)), 1);
}
