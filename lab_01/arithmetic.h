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
    short int divided_num_len = strlen(divided_num->mantissa_part);
    short int divider_num_len = strlen(divider_num->mantissa_part);

    if (divided_num_len > divider_num_len)
    {
        return TRUE;
    }

    if (divided_num_len < divider_num_len)
    {
        return FALSE;
    }

    short int compare_range = strcmp(divided_num->mantissa_part, divider_num->mantissa_part);

    if (compare_range == 0)
    {
        return EQUAL;
    }

    if (compare_range > 0)
    {
        return TRUE;
    }

    if (compare_range < 0)
    {
        return FALSE;
    }
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