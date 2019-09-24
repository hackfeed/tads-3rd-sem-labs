/*
Arithmetic operations interface's header.
*/

int is_greater(num_t *const divided_num, num_t *const divider_num);

int is_nil(const num_t *const structed_num);

int mantissa_subtraction(num_t *const divided_num, num_t *const divider_num);

int count_div_iters(num_t *const divided_num, num_t *const divider_num);

int division_by_subtraction(num_t *const divided_num, num_t *const divider_num, num_t *const result_num);
