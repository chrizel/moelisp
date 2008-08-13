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
    free(o);
}

