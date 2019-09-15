#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"
#include "data_structures.h"

#include "io.h"

#include "parsing.h"
#include "validation.h"
#include "normalization.h"
#include "arithmetic.h"

int main()
{
    long_t int_num, float_num;
    num_t structed_int_num, structed_float_num;

    welcome_print();

    int_input(&int_num);

    if (parse_order_part(int_num, &structed_int_num) == OK)
    {
        short int decided_type = decide_type_by_exp(&structed_int_num);

        if (decided_type == TYPE_INT)
        {
            debug_print(structed_int_num);
        }

        if (decided_type == TYPE_FLOAT)
        {
            printf(ANSI_COLOR_RED
                   "Ошибка типа. Введено действительное число." ANSI_COLOR_RESET);

            return TYPE_ERROR;
        }

        if (decided_type == VALIDATION_ERROR)
        {
            printf(ANSI_COLOR_RED
                   "Ошибка ввода. Соблюдайте правила ввода." ANSI_COLOR_RESET);

            return PARSE_ERROR;
        }
    }

    else
    {
        printf(ANSI_COLOR_RED
               "Ошибка ввода. Соблюдайте правила ввода." ANSI_COLOR_RESET);

        return PARSE_ERROR;
    }

    float_input(&float_num);

    if (parse_order_part(float_num, &structed_float_num) == OK)
    {
        short int decided_type = decide_type_by_exp(&structed_float_num);

        if (decided_type == TYPE_FLOAT)
        {
            debug_print(structed_float_num);
        }

        if (decided_type == TYPE_INT)
        {
            printf(ANSI_COLOR_RED
                   "Ошибка типа. Введено целое число." ANSI_COLOR_RESET);

            return TYPE_ERROR;
        }

        if (decided_type == VALIDATION_ERROR)
        {
            printf(ANSI_COLOR_RED
                   "Ошибка ввода. Соблюдайте правила ввода." ANSI_COLOR_RESET);

            return PARSE_ERROR;
        }
    }

    else
    {
        printf(ANSI_COLOR_RED
               "Ошибка ввода. Соблюдайте правила ввода." ANSI_COLOR_RESET);

        return PARSE_ERROR;
    }
}