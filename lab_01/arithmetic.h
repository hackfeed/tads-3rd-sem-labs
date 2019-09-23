/*
Decide which num is greater.

Input data:
* num_t *const divided_num, divider_num - numbers for comparison.

Output data:
* Return code - TRUE (if divided_num is greater),
FALSE (if divider_num is greater), EQUAL (if nums are equal).
*/
int is_greater(num_t *const divided_num, num_t *const divider_num)
{
    short int num_len = strlen(divided_num->mantissa_part);

    for (short int letter_ind = 0; letter_ind < num_len; ++letter_ind)
    {
        if (divided_num->mantissa_part[letter_ind] >
            divider_num->mantissa_part[letter_ind])
        {
            return TRUE;
        }

        else
        {
            if (divided_num->mantissa_part[letter_ind] <
                divider_num->mantissa_part[letter_ind])
            {
                return FALSE;
            }
        }
    }

    return EQUAL;
}

/*
Check if num is nil.

Input data:
* const num_t *const structed_num - number to be checked.

Output data:
* Return code - IS_NIL or NOT_NIL.
*/
int is_nil(const num_t *const structed_num)
{
    short int num_len = strlen(structed_num->mantissa_part);

    for (short int el_ind = 0; el_ind < num_len; ++el_ind)
    {
        if (structed_num->mantissa_part[el_ind] != '0')
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*
Divide long int by long float using subtraction.

Input data:
* num_t *const divided_num - num to be divided.
* num_t *const divider_num - divider for division.
* num_t *const result_num - divisioned result num.

Output data:
* Return code - OK or OVERFLOW_ERROR.
*/
int division_by_subtraction(num_t *const divided_num,
                            num_t *const divider_num,
                            num_t *const result_num)
{
    short int which_greater = is_greater(divided_num, divider_num);

    if (which_greater == EQUAL)
    {
        if (divided_num->num_sign != divider_num->num_sign)
        {
            result_num->num_sign = NEGATIVE;
        }

        else
        {
            result_num->num_sign = POSITIVE;
        }

        result_num->mantissa_part[0] = '1';
        result_num->mantissa_part[1] = '\0';
        result_num->order_int = divided_num->order_int - divider_num->order_int + 1;

        return OK;
    }

    if (which_greater == TRUE)
    {
        puts("I'm bigger");

        return OK;
    }

    if (which_greater == FALSE)
    {
        puts("I'm lesser");

        return FALSE;
    }
}