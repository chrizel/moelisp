#include "cons.h"
#include "number.h"
#include "object.h"
#include "symbol.h"

pobject eval(pobject env, pobject code)
{
    if (is_cons(code)) {
        pobject proc = eval(env, cons_car(code));
        if (is_func(proc)) {
            pobject tmp = cons_cdr(code);
            pobject params = NIL;
            while (tmp) {
                cons_list_append(&params, eval(env, cons_car(tmp)));
                tmp = cons_cdr(tmp);
            }
            return proc->data.func(params);
        }
    } else if (is_symbol(code)) {
        return cons_assoc_lookup(env, code);
    } else {
        return code;
    }

    return NIL;
}

