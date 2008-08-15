#ifndef CONS_H
#define CONS_H

#include "object.h"

extern pobject cons_new(pobject car, pobject cdr);

extern void cons_assoc_set(pobject *list, pobject key, pobject value);
extern pobject cons_assoc_lookup(pobject list, pobject key);

extern void cons_list_append(pobject *list, pobject o);
extern pobject cons_list_last(pobject list);

extern void cons_stack_push(pobject *stack, pobject o);
extern pobject cons_stack_pop(pobject *stack);

static inline pobject cons_car(pobject o) { return o->data.cons.car; }
static inline pobject cons_cdr(pobject o) { return o->data.cons.cdr; }
static inline void cons_car_set(pobject o, pobject car) { o->data.cons.car = car; }
static inline void cons_cdr_set(pobject o, pobject cdr) { o->data.cons.cdr = cdr; }

#endif
