/*
Number parsing interface's header.
*/

int parse_sign(const long_t entered_num, num_t *const parsed_num);

int parse_dot(const long_t entered_num, num_t *const parsed_num);

int parse_exp_sign(const long_t entered_num, num_t *const parsed_num);

int parse_mantissa_part(const long_t entered_num, num_t *const parsed_num);

int parse_order_part(const long_t entered_num, num_t *const parsed_num);
