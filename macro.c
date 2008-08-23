#include "macro.h"
#include "cons.h"
#include "env.h"
#include "eval.h"
#include "object.h"
#include "print.h"
#include "symbol.h"

pobject macro_new(pobject env, pobject params, pobject code)
{
    pobject o = object_new(T_MACRO);
    o->data.macro.env = env;
    o->data.macro.code = cons_new(params, object_prepend_begin(code));
    return o;
}

pobject macro_expand(pobject call_env, pobject macro, pobject params)
{
    pobject symbol, values;
    pobject params_symbols = cons_car( macro->data.macro.code );
    pobject code = cons_cdr( macro->data.macro.code );
    pobject env  = cons_new( symbol_parent_env, 
                       cons_new( macro->data.macro.env, NIL ) );

    while (params_symbols) {
        symbol = cons_car(params_symbols);
        if (!is_symbol(symbol))
            break;

        if (symbol_ends_with_three_dots(symbol)) {
            symbol = symbol_intern_by_slice(symbol_value(symbol), 0, 
                                            symbol_length(symbol) - 3);
            values = NIL;
            while (params) {
                cons_list_append(&values, cons_car( params ) );
                params = cons_cdr(params);
            }
            env = cons_new( symbol, cons_new( values, env ) );
            break;
        } else {
            env = cons_new( symbol,
                      cons_new( cons_car( params ), env ) );
            params_symbols = cons_cdr(params_symbols);
            params = cons_cdr(params);
        }
    }

    return eval(env, code);
}

pobject macro_eval(pobject call_env, pobject macro, pobject params)
{
    return eval(call_env, macro_expand(call_env, macro, params));
}

