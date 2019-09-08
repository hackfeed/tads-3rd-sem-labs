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

void num_t_print(const num_t structed_num)
{
    printf("%c\n", structed_num.num_sign);
    printf("%s\n", structed_num.mantissa_part);
    printf("%s\n", structed_num.order_part);
    printf("%d\n", structed_num.dot_position);
    printf("%d\n", structed_num.exp_position);
    printf("%d\n", structed_num.order_int);
}

int main()
{
    long_t entered_num;
    num_t structed_num;

    input_long_t_num(&entered_num);
    printf("%s\n", entered_num);
    if (parse_order_part(entered_num, &structed_num) == OK)
    {
        printf("Parsing done without errors. \n");
        if (validate_int_exp_equation(&structed_num) == OK)
        {
            printf("Validation done without errors.\n");
            num_t_print(structed_num);
            return OK;
        }
    }

    num_t_print(structed_num);

    return VALIDATION_ERROR;
}