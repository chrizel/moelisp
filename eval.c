#include "closure.h"
#include "cons.h"
#include "number.h"
#include "object.h"
#include "symbol.h"

pobject eval(pobject env, pobject code)
{
    if (is_cons(code)) {
        pobject proc = eval(env, cons_car(code));
        if (is_cfunc(proc))
            return proc->data.cfunc(env, cons_cdr(code));
        else if (is_closure(proc)) {
            return closure_eval(env, proc, cons_cdr(code));
        }
    } else if (is_symbol(code)) {
        pobject cons = cons_assoc_lookup(env, code);
        return cons ? cons_car(cons) : NIL;
    } else {
        return code;
    }

    return NIL;
}
