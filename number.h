#ifndef NUMBER_H
#define NUMBER_H

#include "object.h"

extern pobject number_new(double value);
extern pobject number_new_by_slice(char *string, int start, int end);
static inline double number_value(pobject p) { return p->data.number; }

#endif
