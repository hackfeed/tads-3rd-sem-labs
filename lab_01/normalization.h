/*
Normalization of structed num.
Normalization means xxxxxxE+-yyyy representation.

Input data:
* num_t *const structed_num - number to be normalized.
*/
void base_mantissa_normalization(num_t *const structed_num)
{
    short int mantissa_len = strlen(structed_num->mantissa_part);

    if (structed_num->dot_position != -2)
    {
        for (short int letter_ind = structed_num->dot_position;
             letter_ind < mantissa_len;
             ++letter_ind)
        {
            structed_num->mantissa_part[letter_ind] =
                structed_num->mantissa_part[letter_ind + 1];
        }

        structed_num->mantissa_part[mantissa_len - 1] = '\0';
        structed_num->order_int += -1 * (mantissa_len - structed_num->dot_position - 1);
    }
}

/*
Presubtraction normalization. Get both of numbers have same lenghth.
Normalization means xxxxxxE+-yyyy representation.

Input data:
* num_t *const divided_num, divider_num - number to be normalized.
*/
void presub_mantissa_normalization(num_t *const divided_num, num_t *const divider_num)
{
    short int divided_num_len = strlen(divided_num->mantissa_part);
    short int divider_num_len = strlen(divider_num->mantissa_part);

    if (divided_num_len < divider_num_len)
    {
        while (divided_num_len < divider_num_len)
        {
            divided_num->mantissa_part[divided_num_len] = '0';
            divided_num->mantissa_part[divided_num_len + 1] = '\0';
            divided_num->order_int -= 1;

            divided_num_len = strlen(divided_num->mantissa_part);
        }
    }

    if (divider_num_len < divided_num_len)
    {
        while (divider_num_len < divided_num_len)
        {
            divider_num->mantissa_part[divider_num_len] = '0';
            divider_num->mantissa_part[divider_num_len + 1] = '\0';
            divider_num->order_int -= 1;

            divider_num_len = strlen(divider_num->mantissa_part);
        }
    }
}