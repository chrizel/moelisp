#ifndef SYMBOL_H
#define SYMBOL_H

#include "object.h"

extern pobject symbol_intern(char *value);
extern pobject symbol_intern_by_slice(char *value, int start, int end);
extern int symbol_ends_with_three_dots(pobject symbol);

static inline char *symbol_value(pobject o) { return o->data.symbol.value; }
static inline void symbol_value_set(pobject o, char *v) { o->data.symbol.value = v; }
static inline int symbol_length(pobject o) { return o->data.symbol.length; }

#endif
