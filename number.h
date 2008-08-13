#ifndef NUMBER_H
#define NUMBER_H

#include "object.h"

extern pobject number_new(double value);
static inline double number_value(pobject p) { return p->data.number; }

#endif
