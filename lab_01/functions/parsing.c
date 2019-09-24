/*
Number parsing interface.
*/

#include <string.h>
#include <ctype.h>
#include "../headers/defines.h"
#include "../headers/data_structures.h"

/* 
Parsing number sign from long_t to num_t struct.

Input data:
* const long_t entered_num - initial entered number.
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK or SIGN_PARSE_ERROR.
*/
int parse_sign(const long_t entered_num, num_t *const parsed_num)
{
    if (entered_num[0] == '-')
    {
        parsed_num->num_sign = NEGATIVE;

        return OK;
    }

    if (entered_num[0] == '+')
    {
        parsed_num->num_sign = POSITIVE;

        return OK;
    }

    return SIGN_PARSE_ERROR;
}

/* 
Parsing float dot position from long_t to num_t struct.

Input data:
* const long_t entered_num - initial entered number.
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK, PARSE_ERROR or DOT_PARSE_ERROR.
*/
int parse_dot(const long_t entered_num, num_t *const parsed_num)
{
    if (parse_sign(entered_num, parsed_num) != OK)
    {
        return PARSE_ERROR;
    }

    short int entered_num_len = strlen(entered_num);

    short int letter_ind = 0;
    short int dot_pos = -1, dot_flag = FALSE;

    while (letter_ind < entered_num_len)
    {
        if (entered_num[letter_ind] == '.')
        {
            if (!dot_flag)
            {
                dot_pos = letter_ind;
                dot_flag = TRUE;
            }

            else
            {
                return DOT_PARSE_ERROR;
            }
        }

        letter_ind++;
    }

    parsed_num->dot_position = dot_pos - 1;

    return OK;
}

/* 
Parsing exponent sign position from long_t to num_t struct.

Input data:
* const long_t entered_num - initial entered number.
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK or PARSE_ERROR.
*/
int parse_exp_sign(const long_t entered_num, num_t *const parsed_num)
{
    if (parse_dot(entered_num, parsed_num) != OK)
    {
        return PARSE_ERROR;
    }

    short int entered_num_len = strlen(entered_num);

    short int letter_ind = 0;
    short int exp_pos;

    while (letter_ind < entered_num_len)
    {
        if (toupper(entered_num[letter_ind]) == 'E')
        {
            exp_pos = letter_ind--;
            break;
        }

        letter_ind++;
    }

    if (letter_ind == entered_num_len)
    {
        exp_pos = -1;
    }

    parsed_num->exp_position = exp_pos;

    return OK;
}

/* 
Parsing mantissa part from long_t to num_t struct.

Input data:
* const long_t entered_num - initial entered number.
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK, PARSE_ERROR or MANTISSA_PARSE_ERROR.
*/
int parse_mantissa_part(const long_t entered_num, num_t *const parsed_num)
{
    if (parse_exp_sign(entered_num, parsed_num) != OK)
    {
        return PARSE_ERROR;
    }

    short int start_cut_pos = 1;
    short int end_cut_pos =
        parsed_num->exp_position == -1 ? strlen(entered_num) : parsed_num->exp_position;

    if (parsed_num->dot_position == -2 &&
            end_cut_pos - start_cut_pos > MAX_INT_NUM_LEN ||
        parsed_num->dot_position != -2 &&
            end_cut_pos - start_cut_pos > MAX_INT_NUM_LEN + 1)
    {
        return MANTISSA_PARSE_ERROR;
    }

    while (start_cut_pos < end_cut_pos)
    {
        parsed_num->mantissa_part[start_cut_pos - 1] = entered_num[start_cut_pos];
        start_cut_pos++;
    }

    parsed_num->mantissa_part[start_cut_pos - 1] = '\0';

    return OK;
}

/* 
Parsing post-exponent order part from long_t to num_t struct.

Input data:
* const long_t entered_num - initial entered number.
* num_t *const parsed_num -  parsed long_t num into num_t struct. 

Output data:
Return code - OK, PARSE_ERROR or ORDER_PARSE_ERROR.
*/
int parse_order_part(const long_t entered_num, num_t *const parsed_num)
{
    if (parse_mantissa_part(entered_num, parsed_num) != OK)
    {
        return PARSE_ERROR;
    }

    short int entered_num_len = strlen(entered_num);

    if (parsed_num->exp_position == -1)
    {
        parsed_num->order_part[0] = '+';
        parsed_num->order_part[1] = '0';
        parsed_num->order_part[2] = '\0';

        return OK;
    }

    short int start_cut_pos = parsed_num->exp_position + 1,
              end_cut_pos = entered_num_len;

    if (end_cut_pos - start_cut_pos > MAX_ORDER_PART_LEN - 1)
    {
        return ORDER_PARSE_ERROR;
    }

    short int letter_ind = 0;

    while (start_cut_pos < end_cut_pos)
    {
        parsed_num->order_part[letter_ind] = entered_num[start_cut_pos];
        letter_ind++;
        start_cut_pos++;
    }

    parsed_num->order_part[letter_ind] = '\0';

    return OK;
}