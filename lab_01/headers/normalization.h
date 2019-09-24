/*
Number normalization interface's header.
*/

void base_mantissa_normalization(num_t *const structed_num);

void remove_leading_zeros(num_t *const structed_num);

void add_one_leading_zero(num_t *const structed_num);

void remove_post_zeros(num_t *const structed_num);

void presub_mantissa_normalization(num_t *const divided_num, num_t *const divider_num);

void mantissa_offset(num_t *const structed_num, const int offset_rate);