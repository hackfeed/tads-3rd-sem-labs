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

/*void presub_mantissa_normalization(num_t *const divided_num, num_t *const divider_num)
{

}*/