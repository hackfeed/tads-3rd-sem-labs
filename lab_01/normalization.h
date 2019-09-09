/*
Normalization of structed num.
Normalization means .xxxxxxE+-yyyy representation.

Input data:
* num_t *const structed_num - number to be normalized.

Output data:
Return code - OK.
*/
int normalize_structed_mantissa(num_t *const structed_num)
{
    if (structed_num->dot_position == -2)
    {
        short int mantissa_len = strlen(structed_num->mantissa_part);
        structed_num->order_int += mantissa_len;

        for (short int i = mantissa_len; i > 0; --i)
        {
            structed_num->mantissa_part[i] = structed_num->mantissa_part[i - 1];
        }

        structed_num->mantissa_part[mantissa_len + 1] = '\0';
    }

    for (short int i = structed_num->dot_position; i > 0; --i)
    {
        structed_num->mantissa_part[i] = structed_num->mantissa_part[i - 1];
    }

    structed_num->mantissa_part[0] = '.';
    structed_num->order_int += structed_num->dot_position;

    return OK;
}