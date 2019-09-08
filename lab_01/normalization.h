int normalize_float_num_t(num_t *const structed_num)
{
    for (short int i = structed_num->dot_position; i > 0; --i)
    {
        structed_num->mantissa_part[i] = structed_num->mantissa_part[i - 1];
    }

    structed_num->mantissa_part[0] = '.';
    structed_num->order_int += structed_num->dot_position;

    return OK;
}