#include <stdlib.h>

#include "object.h"

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

