#include <stdio.h>

#include "cons.h"
#include "gc.h"
#include "object.h"
#include "print.h"

#define GC_FLAG_ON (1 << 4)

static pobject gc_list = NIL;
static int gc_objects = 0;

static inline int gc_flag_get(pobject o)
    { return o->flags & 0x10; }
static inline void gc_flag_set(pobject o, int value)
    { o->flags = (value & 0x10) | (o->flags & 0xef); }
static inline void gc_free(pobject o)
    { --gc_objects; object_free(o); }

static void gc_traverse(pobject env)
{
    pobject object;
    while (is_cons(env)) {
        gc_flag_set(env, GC_FLAG_ON);
        object = cons_car(env);
        if (object && (gc_flag_get(object) == 0)) {
            /*
            printf("%p\n", object);
            */
            gc_flag_set(object, GC_FLAG_ON);

            /* XXX: dotted list support??? */
            if (is_cons(object)) {
                gc_traverse(object);
            } else if (is_closure(object)) {
                gc_traverse(object->data.closure.env);
                gc_traverse(object->data.closure.code);
            } else if (is_macro(object)) {
                gc_traverse(object->data.macro.env);
                gc_traverse(object->data.macro.code);
            }

        }
        env = cons_cdr(env);
    }
}

void gc_collect(pobject env)
{
    int collected = 0;
    int old_count = gc_objects;
    pobject prev, cur, object;

    /* set gc flag of all gc_list objects to 0 */
    cur = gc_list;
    while (cur) {
        gc_flag_set(cons_car(cur), 0);
        cur = cons_cdr(cur);
    }

    /* traverse environment and set gc flag of all objects to 1 */
    gc_traverse(env);

    /* go through gc_list a second time and free all all objects
     * with flag 0 */
    prev = NIL;
    cur = gc_list;
    while (cur) {
        object = cons_car(cur);
        if (gc_flag_get(object) == 0) {
            gc_free(object);
            collected++;
            if (prev) {
                cons_cdr_set(prev, cons_cdr(cur));
                object_free(cur);
                cur = cons_cdr(prev);
            } else {
                gc_list = cons_cdr(cur);
                object_free(cur);
                cur = gc_list;
            }
        } else {
            prev = cur;
            cur = cons_cdr(cur);
        }
    }

    printf("\ngc_collect: %d of %d objects collected\n", collected, old_count);
}

void gc_collect_if_required(pobject env)
{
    /*
    static int object_space = (sizeof (struct object)) * 2;
    TODO
    */
}

pobject gc_add(pobject object)
{
    if (object && !is_symbol(object) && !(object->flags & 0x20)) {
        gc_list = cons_new(object, gc_list);
        object->flags |= 0x20;
        ++gc_objects;
    }
    return object;
}

