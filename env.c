#include "cons.h"
#include "env.h"
#include "object.h"

pobject env_define(pobject env, pobject symbol, pobject value)
{
    if (is_symbol(symbol)) {
        pobject result = cons_assoc_lookup(env, symbol);
        if (result)
            cons_car_set( result, value );
        else
            cons_cdr_set( cons_list_last( env ), 
                            cons_new( symbol, cons_new( value, NIL ) ) );
    }
    return value;
}

pobject env_lookup(pobject env, pobject symbol)
{
    return NIL;
}
