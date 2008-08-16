#include "cfunc.h"
#include "object.h"

pobject cfunc_new(pcfunc func)
{
    pobject o = object_new(T_CFUNC);
    o->data.cfunc = func;
    return o;
}

