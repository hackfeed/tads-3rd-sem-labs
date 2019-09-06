#include <string.h>
#include <ctype.h>

#include "data_structures.h"
#include "defines.h"

int parse_sign(const long_t entered_num, num_t *const validated_num)
{
    if (entered_num[0] == '-')
    {
        validated_num->num_sign = NEGATIVE;

        return OK;
    }

    if (entered_num[0] == '+')
    {
        validated_num->num_sign = POSITIVE;

        return OK;
    }

    return SIGN_PARSE_ERROR;
}

int parse_dot(const long_t entered_num, num_t *const validated_num)
{
    if (parse_sign(entered_num, validated_num) == SIGN_PARSE_ERROR)
    {
        return PARSE_ERROR;
    }

    short int entered_num_len = strlen(entered_num);

    short int i = 0;
    short int dot_pos = -1, dot_flag = FALSE;

    while (i < entered_num_len || toupper(entered_num[i]) != 'E')
    {
        if (entered_num[i] == '.')
        {
            if (!dot_flag)
            {
                dot_pos = i;
                dot_flag = TRUE;
            }

            else
            {
                return DOT_PARSE_ERROR;
            }
        }

        i++;
    }

    validated_num->dot_position = dot_pos;

    return OK;
}

int parse_exp_sign(const long_t entered_num, num_t *const validated_num)
{
    if (parse_dot(entered_num, validated_num) == DOT_PARSE_ERROR)
    {
        return PARSE_ERROR;
    }

    short int entered_num_len = strlen(entered_num);

    short int i = 0;
    short int exp_pos;

    while (i < entered_num_len || toupper(entered_num[i]) != 'E')
    {
        i++;
    }

    if (i == entered_num_len)
    {
        exp_pos = -1;
    }

    else
    {
        exp_pos = i--;
    }

    validated_num->exp_position = exp_pos;

    return OK;
}

int parse_mantissa_part(const long_t entered_num, num_t *const validated_num)
{
    if (parse_exp_sign(entered_num, validated_num) == PARSE_ERROR)
    {
        return PARSE_ERROR;
    }

    short int start_cut_pos = 1, end_cut_pos = validated_num->exp_position;

    if (end_cut_pos - start_cut_pos > MAX_INT_NUM_LEN)
    {
        return MANTISSA_PARSE_ERROR;
    }

    short int i = 0;

    while (start_cut_pos < end_cut_pos)
    {
        validated_num->mantissa_part[i] = entered_num[i];
        i++;
        start_cut_pos++;
    }

    validated_num->mantissa_part[i] = '\0';

    return OK;
}

int parse_order_part(const long_t entered_num, num_t *const validated_num)
{
    if (parse_mantissa_part(entered_num, validated_num) != OK)
    {
        return PARSE_ERROR;
    }

    short int entered_num_len = strlen(entered_num);

    short int start_cut_pos = validated_num->exp_position + 1,
              end_cut_pos = entered_num_len;

    if (end_cut_pos - start_cut_pos > MAX_ORDER_PART_LEN)
    {
        return ORDER_PARSE_ERROR;
    }

    short int i = 0;

    while (start_cut_pos < end_cut_pos)
    {
        validated_num->order_part[i] = entered_num[i];
        i++;
        start_cut_pos++;
    }

    validated_num->order_part[i] = '\0';

    return OK;
}