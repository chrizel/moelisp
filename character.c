#include "object.h"
#include "character.h"

pobject character_new(int value)
{
    pobject o = object_new(T_CHARACTER);
    o->data.character = value;
    return o;
}

