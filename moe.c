#include <stdio.h>

#include "cons.h"
#include "eval.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "read.h"
#include "symbol.h"

static pobject plus(pobject params)
{
    float result = 0;
    while (is_cons(params)) {
        pobject o = cons_car(params);
        if (is_number(o))
            result += number_value(o);
        params = cons_cdr(params);
    }

    return number_new(result);
}

static pobject mult(pobject params)
{
    float result = 1;
    while (is_cons(params)) {
        pobject o = cons_car(params);
        if (is_number(o))
            result *= number_value(o);
        params = cons_cdr(params);
    }

    return number_new(result);
}

int main(int argc, char *argv[])
{
    pobject env = NIL;
    pobject p;

    p = object_new(T_FUNC);
    p->data.func = plus;
    cons_assoc_set(&env, symbol_intern("+"), p);

    p = object_new(T_FUNC);
    p->data.func = mult;
    cons_assoc_set(&env, symbol_intern("*"), p);

    cons_assoc_set(&env, symbol_intern("foo"), number_new(42));
    cons_assoc_set(&env, symbol_intern("bar"), number_new(3.14));
    cons_assoc_set(&env, symbol_intern("baz"), number_new(100));

    if (argc > 1)
        println(eval(env, read(argv[1])));
    
    return 0;
}
