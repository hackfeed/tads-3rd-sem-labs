void num_t_print(const num_t structed_num)
{
    printf("Parsed sign: %c\n",
           structed_num.num_sign);
    printf("Parsed mantissa: %s\n",
           structed_num.mantissa_part);
    printf("Parsed order: %s\n",
           structed_num.order_part);
    printf("Parsed dot position (-2 if absent): %d\n",
           structed_num.dot_position);
    printf("Parsed exponent position (-1 if absent): %d\n",
           structed_num.exp_position);
    printf("Represented order in int: %d\n",
           structed_num.order_int);
}