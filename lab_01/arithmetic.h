/*
Decide which num is greater.

Input data:
* num_t *const divided_num, divider_num - numbers for comparison.

Output data:
* Return code - TRUE (if divided_num is greater or equal),
FALSE (if divider_num is greater).
*/
int is_greater(num_t *const divided_num, num_t *const divider_num)
{
    short int num_len = strlen(divided_num->mantissa_part);

    for (short int letter_ind = 0; letter_ind < num_len; ++letter_ind)
    {
        if ((int)(divided_num->mantissa_part[letter_ind] -
                  divider_num->mantissa_part[letter_ind]) > 0)
        {
            return TRUE;
        }

        else
        {
            if ((int)(divided_num->mantissa_part[letter_ind] -
                      divider_num->mantissa_part[letter_ind]) < 0)
            {
                return FALSE;
            }
        }
    }

    return TRUE;
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
Preparation for classic division algorithm.

Input data:
* num_t *const divided_num, num_t *const divider_num - divided and divider numbers.

Output data:
* Return code - OK or MANTISSA_SUBTRACTION_ERROR.
*/
int mantissa_subtraction(num_t *const divided_num, num_t *const divider_num)
{
    if (is_greater(divided_num, divider_num) == TRUE)
    {
        for (short int base = strlen(divider_num->mantissa_part) - 1; base >= 0; --base)
        {
            if (divided_num->mantissa_part[base] - divider_num->mantissa_part[base] >= 0)
            {
                divided_num->mantissa_part[base] -= divider_num->mantissa_part[base] - '0';
            }

            else
            {
                short int new_base = base - 1;

                while (divided_num->mantissa_part[new_base] - '0' == 0)
                {
                    new_base--;
                }

                divided_num->mantissa_part[new_base]--;
                new_base++;

                for (; new_base < base; new_base++)
                {
                    divided_num->mantissa_part[new_base] += 9;
                }

                divided_num->mantissa_part[base] += 10 - (divider_num->mantissa_part[base] - '0');
            }
        }

        return OK;
    }

    return MANTISSA_SUBTRACTION_ERROR;
}

/*
Count amount of possible subtractions.

Input data:
* num_t *const divided_num, num_t *const divider_num - divided and divider numbers.

Output data:
* iters - found amount of possible subtractions.
*/
int count_div_iters(num_t *const divided_num, num_t *const divider_num)
{
    short int iters = 0;

    while (mantissa_subtraction(divided_num, divider_num) == OK)
    {
        iters++;
    }

    mantissa_offset(divided_num, 1);

    return iters;
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
    short int if_nil_divided = is_nil(divided_num);
    short int if_nil_divider = is_nil(divider_num);

    if (if_nil_divider == TRUE)
    {
        printf(ANSI_COLOR_RED "Ошибка! Деление на ноль!\n" ANSI_COLOR_RESET);

        return DIVISION_BY_ZERO_ERROR;
    }

    if (if_nil_divided == TRUE)
    {
        result_num->num_sign = POSITIVE;
        result_num->mantissa_part[0] = '0';
        result_num->mantissa_part[1] = '\0';
        result_num->order_int = 0;

        return OK;
    }

    if (abs(divided_num->order_int - divider_num->order_int) > 99999)
    {
        printf(ANSI_COLOR_RED "Ошибка! Переполнение порядка!" ANSI_COLOR_RESET);

        return OVERFLOW_ERROR;
    }

    if (is_greater(divided_num, divider_num) != TRUE)
    {
        divided_num->order_int -= 1;
        mantissa_offset(divided_num, 1);
    }

    result_num->mantissa_part[0] = '0';
    short int temp = count_div_iters(divided_num, divider_num);
    result_num->mantissa_part[1] = '0' + temp;

    short int iters;

    for (iters = 2; iters < MAX_MANTISSA_PART_LEN - 1; ++iters)
    {
        if (is_nil(divided_num))
        {
            result_num->mantissa_part[iters] = '\0';
            temp = 0;
            break;
        }

        if (!is_greater(divided_num, divider_num))
        {
            mantissa_offset(divided_num, 1);
            result_num->mantissa_part[iters] = '0';
        }

        else
        {
            temp = count_div_iters(divided_num, divider_num);
            result_num->mantissa_part[iters] = '0' + temp;
        }
    }

    result_num->mantissa_part[MAX_MANTISSA_PART_LEN - 1] = '\0';
    if ((iters == MAX_MANTISSA_PART_LEN - 1) && (temp = count_div_iters(divided_num, divider_num)) >= 5)
    {
        result_num->mantissa_part[MAX_MANTISSA_PART_LEN - 2] += 1;
    }

    for (; iters < MAX_MANTISSA_PART_LEN - 1; ++iters)
    {
        result_num->mantissa_part[iters] = '0';
    }

    result_num->mantissa_part[MAX_MANTISSA_PART_LEN - 1] = '\0';

    short int inc = FALSE;

    for (iters = MAX_MANTISSA_PART_LEN - 2; iters >= 0; --iters)
    {
        result_num->mantissa_part[iters] += inc;

        if (result_num->mantissa_part[iters] == ':')
        {
            result_num->mantissa_part[iters] = '0';
            inc = TRUE;
        }

        else
        {
            break;
        }
    }

    if (result_num->mantissa_part[0] == '1')
    {
        for (iters = MAX_MANTISSA_PART_LEN - 2; iters > 0; --iters)
        {
            result_num->mantissa_part[iters] = result_num->mantissa_part[iters - 1];
        }

        result_num->mantissa_part[0] = '0';
    }

    else
    {
        inc = FALSE;
    }

    result_num->mantissa_part[MAX_MANTISSA_PART_LEN - 3] = '\0';

    if (divided_num->num_sign != divider_num->num_sign)
    {
        result_num->num_sign = NEGATIVE;
    }

    else
    {
        result_num->num_sign = POSITIVE;
    }

    result_num->order_int = divided_num->order_int - divider_num->order_int + 1 + inc;
    if (result_num->order_int > 99999)
    {
        return OVERFLOW_ERROR;
    }

    return OK;
}