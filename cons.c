#include "object.h"
#include "cons.h"

pobject cons_new(pobject car, pobject cdr)
{
    pobject o = object_new(T_CONS);
    cons_car_set(o, car);
    cons_cdr_set(o, cdr);
    return o;
}

pobject cons_assoc_lookup(pobject list, pobject key)
{
    if (is_cons(list)) {
        while (is_cons(cons_cdr(list))) {
            if (cons_car(list) == key)
                return cons_car(cons_cdr(list));
            list = cons_cdr(cons_cdr(list));
        }
    }

    return NIL;
}

