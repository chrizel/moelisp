#include "closure.h"
#include "cons.h"
#include "env.h"
#include "eval.h"
#include "gc.h"
#include "object.h"
#include "print.h"
#include "symbol.h"

pobject closure_new(pobject env, pobject params, pobject code)
{
    pobject o = object_new(T_CLOSURE);
    o->data.closure.env = env;
    o->data.closure.code = gc_add( cons_new(params, object_prepend_begin(code)) );
    return o;
}

pobject closure_eval(pobject call_env, pobject closure, pobject params)
{
    pobject symbol, values;
    pobject params_symbols = cons_car( closure->data.closure.code );
    pobject code = cons_cdr( closure->data.closure.code );
    pobject env  = gc_add( cons_new( symbol_parent_env, 
                       gc_add( cons_new( closure->data.closure.env, NIL ) ) ) );

    while (params_symbols) {
        symbol = cons_car(params_symbols);
        if (!is_symbol(symbol))
            break;

        if (symbol_ends_with_three_dots(symbol)) {
            symbol = symbol_intern_by_slice(symbol_value(symbol), 0, 
                                            symbol_length(symbol) - 3);
            values = NIL;
            while (params) {
                cons_list_append(&values, eval( call_env, cons_car( params ) ), 1);
                params = cons_cdr(params);
            }
            env = gc_add( cons_new( symbol, gc_add( cons_new( values, env ) ) ) );
            break;
        } else {
            env = gc_add( cons_new( symbol,
                      gc_add( cons_new( eval( call_env, cons_car( params ) ), env ) ) ) );
            params_symbols = cons_cdr(params_symbols);
            params = cons_cdr(params);
        }
    }

    return eval(env, code);
}

