#include <stdio.h>

#include "cons.h"
#include "number.h"
#include "object.h"
#include "print.h"
#include "read.h"
#include "symbol.h"

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

    read("(+ hello world test)");

    print(list);
    printf("\n\n");

    cons_list_append(&list, symbol_new("foo"));
    cons_list_append(&list, symbol_new("bar"));
    print(list);

    /*
    print(cons_new(symbol_new("+"),
                cons_new(number_new(1),
                    cons_new(
                        cons_new(symbol_new("*"),
                            cons_new(number_new(2),
                                cons_new(number_new(3),
                                    NIL))), NIL))));
                                    */

    printf("\n\n");
        
    return 0;
}
