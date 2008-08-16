#include <math.h>

#include "builtin_math.h"
#include "cfunc.h"
#include "cons.h"
#include "eval.h"
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

    return number_new(result);
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

    return number_new(result);
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

    return number_new(result);
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

    return number_new(result);
}

void builtin_math_init(pobject *env)
{
    cons_assoc_set(env, symbol_intern("*pi*"), number_new(M_PI));

    cons_assoc_set(env, symbol_intern("+"), cfunc_new(plus));
    cons_assoc_set(env, symbol_intern("-"), cfunc_new(minus));
    cons_assoc_set(env, symbol_intern("*"), cfunc_new(mult));
    cons_assoc_set(env, symbol_intern("/"), cfunc_new(div));
}

