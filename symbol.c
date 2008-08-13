#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "symbol.h"

pobject symbol_new(char *value)
{
    return symbol_new_by_slice(value, 0, strlen(value));
}

pobject symbol_new_by_slice(char *value, int start, int end)
{
    int len = end - start;
    pobject o = object_new(T_SYMBOL);
    symbol_value_set(o, malloc(len + 1));
    strncpy(symbol_value(o), value + start, len);
    symbol_value(o)[len] = '\0';
    return o;
}
