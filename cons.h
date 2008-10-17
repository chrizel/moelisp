#ifndef CONS_H
#define CONS_H

#include "object.h"

extern pobject cons_new(pobject car, pobject cdr);

extern void cons_assoc_set(pobject *list, pobject key, pobject value, int gc);
extern pobject cons_assoc_lookup(pobject list, pobject key);

extern void cons_list_append(pobject *list, pobject o, int gc);
extern void cons_list_last_cdr_set(pobject *list, pobject o);
extern pobject cons_list_last(pobject list);
extern int cons_list_length(pobject list);
extern pobject cons_list_find(pobject list, pobject o);

extern void cons_stack_push(pobject *stack, pobject o, int gc);
extern pobject cons_stack_pop(pobject *stack);

static inline pobject cons_car(pobject o) 
    { return is_cons(o) ? o->data.cons.car : NIL;  }
static inline pobject cons_cdr(pobject o) 
    { return is_cons(o) ? o->data.cons.cdr : NIL;  }

static inline pobject cons_nth(pobject o, int nth)
{ 
    for (; is_cons(o) && (nth > 1); --nth)
        o = cons_cdr(o);
    return cons_car(o);
}

static inline void cons_car_set(pobject o, pobject car) 
    { o->data.cons.car = car; }
static inline void cons_cdr_set(pobject o, pobject cdr) 
    { o->data.cons.cdr = cdr; }

#endif
