#ifndef CHARACTER_H
#define CHARACTER_H

#include "object.h"

extern pobject character_new(int value);
static inline int character_value(pobject p) { return p->data.character; }

#endif
