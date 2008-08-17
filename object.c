#include <stdlib.h>

#include "cons.h"
#include "number.h"
#include "object.h"
#include "symbol.h"

pobject object_new(char type)
{
    pobject o = malloc(sizeof(struct object));
    o->flags = type;
    object_new_count++;
    return o;
}

void object_free(pobject o)
{
    if (is_symbol(o))
        free(o->data.symbol);
    free(o);
    object_free_count++;
}

int object_equal(pobject o1, pobject o2)
{
    if (o1 == o2)
        return 1;

    if (object_type(o1) == object_type(o2)) {
        if (is_number(o1)) {
            return number_value(o1) == number_value(o2);
        } else if (is_cons(o1)) {
            do {
                if (!object_equal(cons_car(o1), cons_car(o2)))
                    return 0;
                o1 = cons_cdr(o1);
                o2 = cons_cdr(o2);
            } while (is_cons(o1) && is_cons(o2));
            return object_equal(o1, o2);
        }
    }

    return 0;
}

pobject object_prepend_begin(pobject o)
{
    static pobject begin = NIL;
    if (!begin) begin = symbol_intern("begin");
    return is_cons(o) ? cons_new(begin, o) : o;
}

