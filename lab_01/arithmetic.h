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

    for (short int alpha = 0; alpha < divider_num_len; ++alpha)
    {
        if (divided_num->mantissa_part[alpha] >
                divider_num->mantissa_part[alpha])
        {
            return TRUE;
        }
    }

    return FALSE;
}

void division_by_subtraction(num_t *const divided_num,
                             num_t *const divider_num,
                             num_t *const result_num)
{

}