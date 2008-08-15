#ifndef SYMBOL_H
#define SYMBOL_H

#include "object.h"

extern pobject symbol_intern(char *value);
extern pobject symbol_intern_by_slice(char *value, int start, int end);

static inline char *symbol_value(pobject o) { return o->data.symbol; }
static inline void symbol_value_set(pobject o, char *v) { o->data.symbol = v; }

#endif
