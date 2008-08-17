#include "object.h"
#include "cons.h"

pobject cons_new(pobject car, pobject cdr)
{
    pobject o = object_new(T_CONS);
    cons_car_set(o, car);
    cons_cdr_set(o, cdr);
    return o;
}

void cons_assoc_set(pobject *list, pobject key, pobject value)
{
    if (is_cons(*list)) {
        pobject cur = *list;
        while (cur && is_cons(cons_cdr(cur))) {
            if (cons_car(cur) == key) {
                /* XXX: Memory management??? */
                cons_car_set(cons_cdr(cur), value);
                return;
            }
            cur = cons_cdr(cons_cdr(cur));
        }
    }

    *list = cons_new(key, cons_new(value, *list));
}

pobject cons_assoc_lookup(pobject list, pobject key)
{
    if (is_cons(list)) {
        while (list && is_cons(cons_cdr(list))) {
            if (cons_car(list) == key) {
                return cons_cdr(list);
            }
            list = cons_cdr(cons_cdr(list));
        }
    }

    return NIL;
}

void cons_list_append(pobject *list, pobject o)
{
    pobject cur = *list;
    if (is_cons(cur))
        cons_list_last_cdr_set(list, cons_new(o, NIL));
    else if (is_nil(cur))
        *list = cons_new(o, NIL);
}

void cons_list_last_cdr_set(pobject *list, pobject o)
{
    pobject cur = *list;
    if (is_cons(cur)) {
        while (is_cons(cons_cdr(cur)))
            cur = cons_cdr(cur);
        cons_cdr_set(cur, o);
    }
}

pobject cons_list_last(pobject list)
{
    if (is_cons(list)) {
        while (is_cons(cons_cdr(list)))
            list = cons_cdr(list);
        return list;
    }

    return NIL;
}

void cons_stack_push(pobject *stack, pobject o)
{
    *stack = cons_new(o, *stack);
}

pobject cons_stack_pop(pobject *stack)
{
    if (is_cons(*stack)) {
        pobject result = cons_car(*stack);
        pobject cons = *stack;
        *stack = cons_cdr(cons);
        object_free(cons);
        return result;
    }

    return NIL;
}

