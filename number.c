#include "object.h"
#include "number.h"

pobject number_new(double value)
{
    pobject o = object_new(T_NUMBER);
    o->data.number = value;
    return o;
}

