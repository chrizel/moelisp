#ifndef GC_H
#define GC_h

#include "object.h"

extern pobject gc_add(pobject object);
extern void gc_collect(pobject env);
extern void gc_collect_if_required(pobject env);

static inline pobject gc_add_if(int cond, pobject o)
    { return cond ? gc_add(o) : o; } 
static inline int gc_responsibility(pobject o)
    { return o->flags & 0x20; }

#endif
