#include <stdlib.h>

#include "object.h"
#include "number.h"

pobject object_new(char type)
{
    pobject o = malloc(sizeof(struct object));
    o->flags = type;
    return o;
}

void object_free(pobject o)
{
    if (is_symbol(o))
        free(o->data.symbol);
    free(o);
}

int object_equal(pobject o1, pobject o2)
{
    if (o1 == o2)
        return 1;

    if (object_type(o1) == object_type(o2)) {
        if (is_number(o1)) {
            return number_value(o1) == number_value(o2);
        } else if (is_cons(o1)) {
            /* TODO */
        }
    }

    return 0;
}
