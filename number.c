#include "object.h"
#include "number.h"

pobject number_new(double value)
{
    pobject o = object_new(T_NUMBER);
    o->data.number = value;
    return o;
}

pobject number_new_by_slice(char *string, int start, int end)
{
    double value = 0, prec = 1;
    int i;

    for (i = start; i < end; ++i) {
        if (string[i] == '.') {
            for (++i; i < end; ++i) {
                prec *= 0.1;
                value += (string[i] - '0') * prec;
            }
            break;
        } else {
            value = (value * 10) + (string[i] - '0');
        }
    }

    return number_new(value);
}

