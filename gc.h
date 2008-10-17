#ifndef GC_H
#define GC_h

#include "object.h"

extern pobject gc_add(pobject object);
extern void gc_free(pobject object);
extern void gc_collect(pobject env);

#define GC_FLAG_ON (1 << 4)

static inline int gc_flag_get(pobject o) { return o->flags & 0x10; }
static inline void gc_flag_set(pobject o, int value) 
    { o->flags = (value & 0x10) | (o->flags & 0xef); }
static inline pobject gc_add_if(int cond, pobject o)
    { return cond ? gc_add(o) : o; } 
static inline int gc_responsibility(pobject o)
    { return o->flags & 0x20; }

#endif
