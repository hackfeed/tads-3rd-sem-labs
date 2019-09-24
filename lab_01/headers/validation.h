/*
Parsed number validation interface's header.
*/

int validate_mantissa_part(num_t *const parsed_num);

int validate_order_part(num_t *const parsed_num);

int power(const int base, const int pwr);

int int_represent_order_part(num_t *const parsed_num);

int decide_type_by_exp(num_t *const parsed_num);