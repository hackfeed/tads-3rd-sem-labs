#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"
#include "data_structures.h"

#include "arithmetic.h"
#include "input.h"
#include "parsing.h"
#include "validation.h"
#include "normalization.h"
#include "debug.h"

int main()
{
    long_t entered_num;
    num_t structed_num;

    input_long_t_num(&entered_num);

    if (parse_order_part(entered_num, &structed_num) == OK)
    {
        printf("Parsing done without errors. \n");

        if (decide_type_by_exp(&structed_num) == TYPE_INT)
        {
            printf("Validation done without errors. TYPE_INT\n");
            num_t_print(structed_num);

            return OK;
        }

        if (decide_type_by_exp(&structed_num) == TYPE_FLOAT)
        {
            printf("Validation done without errors. TYPE_FLOAT\n");
            num_t_print(structed_num);

            return OK;
        }
    }

    return VALIDATION_ERROR;
}