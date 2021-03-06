#include <stdio.h>

#include "character.h"
#include "cons.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "symbol.h"

void print(pobject o)
{
    if (is_nil(o))
        printf("nil");
    else if (is_symbol(o))
        printf("%s", symbol_value(o));
    else if (is_character(o))
        printf("#\\%c", character_value(o));
    else if (is_number(o)) {
        double v = number_value(o);
        if (v == (double)((int)v))
            printf("%.0f", v);
        else
            printf("%f", number_value(o));
    } else if (is_cfunc(o))
        printf("#<cfunc:%p>", o->data.cfunc);
    else if (is_closure(o)) {
        printf("#<closure:%p:{", o->data.closure.env);
        print(o->data.closure.code);
        printf("}>");
    } else if (is_macro(o)) {
        printf("#<macro:%p:{", o->data.closure.env);
        print(o->data.closure.code);
        printf("}>");
    } else if (is_cons(o)) {
        printf("(");

        for (; is_cons(o); o = cons_cdr(o)) {
            print(cons_car(o));
            if (!is_nil(cons_cdr(o)))
                printf(" ");
        }

        if (!is_nil(o)) {
            printf(". ");
            print(o);
        }

        printf(")");
    }
}

void println(pobject o)
{
    print(o);
    printf("\n");
}

