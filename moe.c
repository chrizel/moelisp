#include <stdio.h>

#include "cons.h"
#include "number.h"
#include "object.h"

int main(int argc, char *argv[])
{
    int i;
    pobject list;
    pobject nums[6];

    for (i = 0; i < 6; i++)
        nums[i] = number_new(i + 1);

    list = cons_new(nums[0],
            cons_new(nums[1],
             cons_new(nums[2],
              cons_new(nums[3],
               cons_new(nums[4],
                cons_new(nums[5], NIL))))));

    printf("%f\n", number_value(cons_assoc_lookup(list, nums[2])));
        
    return 0;
}
