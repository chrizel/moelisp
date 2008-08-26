#include <stdio.h>

#include "cons.h"
#include "gc.h"
#include "object.h"
#include "print.h"

static pobject gc_list = NIL;

pobject gc_add(pobject object)
{
    if (object && (!is_symbol(object)))
        gc_list = cons_new(object, gc_list);
    return object;
}

void gc_free(pobject object)
{
    pobject prev = NIL, cur;

    /* look for the cons cell in gc_list for object */
    cur = gc_list;
    while (cur) {
        if (cons_car(cur) == object)
            break;
        prev = cur;
        cur = cons_cdr(cur);
    }

    /* set new gc_list connections and free the cur cons cell */
    if (cur) {
        if (prev)
            cons_cdr_set(prev, cons_cdr(cur));
        else
            gc_list = cons_cdr(cur);
        object_free(cur);
    }

    object_free(object);
}

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
            object_free(object);
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

    printf("@@@ %d objects collected\n", collected);
}
