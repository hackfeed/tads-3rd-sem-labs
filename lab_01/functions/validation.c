/*
Parsed number validation interface.
*/

#include <string.h>
#include "../headers/defines.h"
#include "../headers/data_structures.h"

/* 
Checking containing only integer digits in mantissa part of long_t number 
and leading zeros absence.

Input data:
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK or MANTISSA_VALIDATION_ERROR.
*/
int validate_mantissa_part(num_t *const parsed_num)
{
    short int mantissa_len = strlen(parsed_num->mantissa_part);

    if (parsed_num->dot_position == -2)
    {
        for (short int letter_ind = 0; letter_ind < mantissa_len; ++letter_ind)
        {
            if (parsed_num->mantissa_part[letter_ind] < '0' ||
                parsed_num->mantissa_part[letter_ind] > '9')
            {
                return MANTISSA_VALIDATION_ERROR;
            }
        }
    }

    else
    {
        short int end_cut_pos = parsed_num->dot_position;

        parsed_num->mantissa_part[parsed_num->dot_position] = '1';

        for (short int letter_ind = 0; letter_ind < end_cut_pos; ++letter_ind)
        {
            if (parsed_num->mantissa_part[letter_ind] < '0' ||
                parsed_num->mantissa_part[letter_ind] > '9')
            {
                return MANTISSA_VALIDATION_ERROR;
            }
        }

        parsed_num->mantissa_part[parsed_num->dot_position] = '.';
    }

    return OK;
}

/* 
Checking containing only integer digits in order part of long_t number, 
order sign existment and leading zeros absence.

Input data:
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK, VALIDATION_ERROR, ORDER_SIGN_VALIDATION_ERROR 
or ORDER_VALIDATION_ERROR.
*/
int validate_order_part(num_t *const parsed_num)
{
    if (validate_mantissa_part(parsed_num) != OK)
    {
        return VALIDATION_ERROR;
    }

    if (parsed_num->order_part[0] != '+' &&
        parsed_num->order_part[0] != '-')
    {
        return ORDER_SIGN_VALIDATION_ERROR;
    }

    short int order_part_len = strlen(parsed_num->order_part);

    for (short int letter_ind = 1; letter_ind < order_part_len; ++letter_ind)
    {
        if (parsed_num->order_part[letter_ind] < '0' ||
            parsed_num->order_part[letter_ind] > '9')
        {
            return ORDER_VALIDATION_ERROR;
        }
    }

    return OK;
}

/*
Pow function implementation.

Input data:
* const int base - num to be powered.
* const int p - power to be applied to num.

Output data:
* powered num.
*/
int power(const int base, const int pwr)
{
    if (pwr == 0)
    {
        return 1;
    }

    return (base * power(base, pwr - 1));
}

/* 
Creating integer representation of order part in num_t struct.

Input data:
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK or VALIDATION_ERROR.
*/
int int_represent_order_part(num_t *const parsed_num)
{
    if (validate_order_part(parsed_num) != OK)
    {
        return VALIDATION_ERROR;
    }

    short int order_part_len = strlen(parsed_num->order_part);
    int order_part_int = 0;

    for (short int letter_int = 1; letter_int < order_part_len; ++letter_int)
    {
        order_part_int += (parsed_num->order_part[letter_int] - '0') *
                          power(10, order_part_len - letter_int - 1);
    }

    if (parsed_num->order_part[0] == '+')
    {
        parsed_num->order_int = order_part_int;
    }

    else
    {
        parsed_num->order_int = -1 * order_part_int;
    }

    return OK;
}

/*
Validate that integer doesn't contain dot and exponent sign.
Input data:
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK, VALIDATION_ERROR, TYPE_INT or TYPE_FLOAT.
*/
int decide_type_by_exp(num_t *const parsed_num)
{
    if (int_represent_order_part(parsed_num) != OK)
    {
        return VALIDATION_ERROR;
    }

    if (parsed_num->dot_position == -2 &&
        parsed_num->exp_position == -1)
    {
        return TYPE_INT;
    }

    return TYPE_FLOAT;
}