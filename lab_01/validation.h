#include <string.h>
#include <ctype.h>

#include "data_structures.h"

#define OK 0
#define SIGN_VALIDATION_ERROR 1
#define DOT_VALIDATION_ERROR 2

int check_sign(const long_t *const entered_num, num_t *const validated_num)
{
    if (entered_num[0] == '-')
    {
        validated_num->num_sign = NEGATIVE;

        return OK;
    }

    if (entered_num[0] == '+' ||
        entered_num[0] >= '1' ||
        entered_num[0] <= '9')
    {
        validated_num->num_sign = POSITIVE;

        return OK;
    }

    return SIGN_VALIDATION_ERROR;
}

int check_single_dot_exist(const long_t *const entered_num,
                           num_t *const validated_num)
{
    short int entered_num_len = strlen(entered_num);

    short int i = 0;
    short int dots_count = 0, dot_pos = -1, dot_flag = 0;

    while (i < entered_num_len || toupper(entered_num[i]) != 'E')
    {
        if (entered_num[i] == '.')
        {
            dots_count++;
            if (!dot_flag)
            {
                dot_pos = i;
                dot_flag = 1;
            }
        }

        i++;
    }

    if (dots_count == 1)
    {
        validated_num->dot_position = dot_pos;

        return OK;
    }

    return DOT_VALIDATION_ERROR;
}

int check_int_digits_only_contain(const long_t *const entered_num,
                                  num_t *const validated_num)
{
    if (check_sign(entered_num, validated_num)
}