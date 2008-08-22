#include "closure.h"
#include "cons.h"
#include "env.h"
#include "eval.h"
#include "object.h"

pobject closure_new(pobject env, pobject params, pobject code)
{
    pobject o = object_new(T_CLOSURE);
    o->data.closure.env = env;
    o->data.closure.code = cons_new(params, object_prepend_begin(code));
    return o;
}

pobject closure_eval(pobject env, pobject closure, pobject params)
{
    pobject params_symbols = cons_car( closure->data.closure.code );
    pobject code = cons_cdr( closure->data.closure.code );

    /* TODO: make parent environment */
    while (params_symbols) {
        env_define( env, 
                    cons_car( params_symbols ), 
                    eval( env, cons_car( params ) ) );
        params_symbols = cons_cdr(params_symbols);
        params = cons_cdr(params);
    }

    return eval(closure->data.closure.env, code);
}

