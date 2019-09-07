#include <string.h>

#include "data_structures.h"
#include "defines.h"

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

    if (parsed_num->dot_position == -1)
    {
        if (mantissa_len > 1 && parsed_num->mantissa_part[0] == '0')
        {
            return MANTISSA_VALIDATION_ERROR;
        }

        for (short int i = 0; i < mantissa_len; ++i)
        {
            if (parsed_num->mantissa_part[i] < '0' ||
                parsed_num->mantissa_part[i] > '9')
            {
                return MANTISSA_VALIDATION_ERROR;
            }
        }
    }

    else
    {
        short int start_cut_pos = 0, end_cut_pos = parsed_num->dot_position;

        if (end_cut_pos - start_cut_pos > 1 && parsed_num->mantissa_part[0] == '0')
        {
            return MANTISSA_VALIDATION_ERROR;
        }

        parsed_num->mantissa_part[parsed_num->dot_position] = '1';

        for (short int i = 0; i < mantissa_len; ++i)
        {
            if (parsed_num->mantissa_part[i] < '0' ||
                parsed_num->mantissa_part[i] > '9')
            {
                return MANTISSA_VALIDATION_ERROR;
            }
        }
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
    if (validate_mantissa_part(parsed_num) == MANTISSA_VALIDATION_ERROR)
    {
        return VALIDATION_ERROR;
    }

    if (parsed_num->order_part[0] != '+' ||
        parsed_num->order_part[0] != '-')
    {
        return ORDER_SIGN_VALIDATION_ERROR;
    }

    short int order_part_len = strlen(parsed_num->order_part);

    if (order_part_len > 2 && parsed_num->order_part[1] == '0')
    {
        return ORDER_VALIDATION_ERROR;
    }

    for (short int i = 1; i < order_part_len; ++i)
    {
        if (parsed_num->order_part[i] < '0' ||
            parsed_num->order_part[i] > '9')
        {
            return ORDER_VALIDATION_ERROR;
        }
    }

    return OK;
}