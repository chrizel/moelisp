#include "closure.h"
#include "cons.h"
#include "env.h"
#include "eval.h"
#include "gc.h"
#include "macro.h"
#include "object.h"
#include "print.h"
#include "symbol.h"

pobject macro_new(pobject env, pobject params, pobject code)
{
    pobject o = object_new(T_MACRO);
    o->data.closure.env = env;
    o->data.closure.code = gc_add( cons_new(params, object_prepend_begin(code)) );
    return o;
}

pobject macro_expand(pobject call_env, pobject macro, pobject params)
{
    return closure_eval(call_env, macro, params, 0);
}

pobject macro_eval(pobject call_env, pobject macro, pobject params)
{
    return eval(call_env, macro_expand(call_env, macro, params));
}

