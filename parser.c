#include <stdio.h>

#include "object.h"

int main(int argc, char *argv[])
{
    pobject o = object_new(T_NUMBER);
    printf("%d\n", sizeof(*o));
    return 0;
}
