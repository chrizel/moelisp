#include <stdlib.h>
#include <string.h>

#include "cons.h"
#include "object.h"
#include "symbol.h"

static pobject symbol_table = NIL;

static pobject symbol_new_by_slice(char *value, int start, int end)
{
    int len = end - start;
    pobject o = object_new(T_SYMBOL);
    symbol_value_set(o, malloc(len + 1));
    strncpy(symbol_value(o), value + start, len);
    symbol_value(o)[len] = '\0';
    o->data.symbol.length = len;
    return o;
}

pobject symbol_intern(char *value)
{
    return symbol_intern_by_slice(value, 0, strlen(value));
}

pobject symbol_intern_by_slice(char *value, int start, int end)
{
    pobject result = NIL, cur = symbol_table;
    char *str;
    int len = end - start, i;

    while (cur) {
        result = cons_car(cur);
        str = symbol_value(result);
        for (i = 0; i < len; ++i) {
            if ((str[i] == '\0') || (str[i] != value[start + i])) {
                result = NIL;
                break;
            }
        }

        if (result && (str[i] == '\0'))
            return result;

        cur = cons_cdr(cur);
    }

    result = symbol_new_by_slice(value, start, end);
    cons_stack_push(&symbol_table, result);
    return result;
}

int symbol_ends_with_three_dots(pobject symbol)
{
    int len = symbol_length(symbol);
    return (len > 2)
        && (symbol_value(symbol)[len-1] == '.')
        && (symbol_value(symbol)[len-2] == '.')
        && (symbol_value(symbol)[len-3] == '.');
}

