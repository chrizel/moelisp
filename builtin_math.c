#include <math.h>

#include "builtin_math.h"
#include "cfunc.h"
#include "cons.h"
#include "eval.h"
#include "gc.h"
#include "number.h"
#include "object.h"
#include "symbol.h"

static pobject plus(pobject env, pobject params)
{
    float result = 0;
    while (is_cons(params)) {
        pobject o = eval(env, cons_car(params));
        if (is_number(o))
            result += number_value(o);
        params = cons_cdr(params);
    }

    return gc_add(number_new(result));
}

static pobject minus(pobject env, pobject params)
{
    float result = 0;
    pobject o = eval(env, cons_car(params)); 
    if (is_number(o)) {
        result = number_value(o);
        params = cons_cdr(params);
        if (is_cons(params)) {
            while (is_cons(params)) {
                pobject o = eval(env, cons_car(params));
                if (is_number(o))
                    result -= number_value(o);
                params = cons_cdr(params);
            }
        } else {
            result = -result;
        }
    }

    return gc_add(number_new(result));
}

static pobject mult(pobject env, pobject params)
{
    float result = 1;
    while (is_cons(params)) {
        pobject o = eval(env, cons_car(params));
        if (is_number(o))
            result *= number_value(o);
        params = cons_cdr(params);
    }

    return gc_add(number_new(result));
}

static pobject div(pobject env, pobject params)
{
    float result = 0;
    pobject o = eval(env, cons_car(params)); 
    if (is_number(o)) {
        result = number_value(o);
        params = cons_cdr(params);
        if (is_cons(params)) {
            while (is_cons(params)) {
                pobject o = eval(env, cons_car(params));
                if (is_number(o))
                    result /= number_value(o); /* TODO: division by zero error handling */
                params = cons_cdr(params);
            }
        }
    }

    return gc_add(number_new(result));
}

static pobject mod(pobject env, pobject params)
{
    pobject o1 = eval(env, cons_nth(params, 1));
    pobject o2 = eval(env, cons_nth(params, 2));
    return (is_number(o1) && is_number(o2))
         ? gc_add((number_new( (int)number_value(o1) % (int)number_value(o2) )))
         : NIL;
}

void builtin_math_init(pobject *env)
{
    cons_assoc_set(env, symbol_intern("*pi*"), gc_add(number_new(M_PI)), 1);

    cons_assoc_set(env, symbol_intern("+"),   gc_add(cfunc_new(plus)), 1);
    cons_assoc_set(env, symbol_intern("-"),   gc_add(cfunc_new(minus)), 1);
    cons_assoc_set(env, symbol_intern("*"),   gc_add(cfunc_new(mult)), 1);
    cons_assoc_set(env, symbol_intern("/"),   gc_add(cfunc_new(div)), 1);
    cons_assoc_set(env, symbol_intern("mod"), gc_add(cfunc_new(mod)), 1);
}

