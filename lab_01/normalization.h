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

        structed_num->mantissa_part[mantissa_len] = '\0';
        structed_num->order_int += -1 * (mantissa_len - structed_num->dot_position - 1);

        for (short int letter_ind = mantissa_len - 1;
             letter_ind < MAX_MANTISSA_PART_LEN - 1;
             ++letter_ind)
        {
            structed_num->mantissa_part[letter_ind] = '0';
            structed_num->order_int -= 1;
        }
    }

    else
    {
        for (short int letter_ind = mantissa_len;
             letter_ind < MAX_MANTISSA_PART_LEN - 1;
             ++letter_ind)
        {
            structed_num->mantissa_part[letter_ind] = '0';
            structed_num->order_int -= 1;
        }
    }

    structed_num->mantissa_part[MAX_MANTISSA_PART_LEN - 1] = '\0';
}

/*
Remove useless leading zeros in structed number.

Input data:
* num_t *const structed_num - number to be normalised.
*/
void remove_leading_zeros(num_t *const structed_num)
{
    short int num_len = strlen(structed_num->mantissa_part);

    short int cur_digit = 0;

    while (structed_num->mantissa_part[cur_digit] == '0')
    {
        cur_digit++;
    }

    for (short int repeats = 0; repeats < cur_digit; ++repeats)
    {
        for (short int letter_ind = 0; letter_ind < num_len - 1; ++letter_ind)
        {
            char temp = structed_num->mantissa_part[letter_ind];
            structed_num->mantissa_part[letter_ind] =
                structed_num->mantissa_part[letter_ind + 1];
            structed_num->mantissa_part[letter_ind + 1] = temp;
        }
    }

    structed_num->mantissa_part[num_len - cur_digit] = '\0';
}

void add_one_leading_zero(num_t *const structed_num)
{
    short int num_len = strlen(structed_num->mantissa_part);

    for (short int letter_ind = num_len; letter_ind > 0; --letter_ind)
    {
        structed_num->mantissa_part[letter_ind] =
            structed_num->mantissa_part[letter_ind - 1];
    }

    structed_num->mantissa_part[0] = '0';
    structed_num->mantissa_part[num_len + 1] = '\0';
}

void remove_post_zeros(num_t *const structed_num)
{
    short int letter_ind, num_len = strlen(structed_num->mantissa_part);

    letter_ind = num_len - 1;

    while (structed_num->mantissa_part[letter_ind] == '0' && letter_ind > 1)
    {
        letter_ind--;
    }

    structed_num->mantissa_part[letter_ind + 1] = '\0';
}

/*
Presubtraction normalization. Get both of numbers have same lenghth.
Normalization means xxxxxxE+-yyyy representation.

Input data:
* num_t *const divided_num, divider_num - number to be normalized.
*/
void presub_mantissa_normalization(num_t *const divided_num, num_t *const divider_num)
{
    remove_leading_zeros(divided_num);
    remove_leading_zeros(divider_num);

    add_one_leading_zero(divided_num);
    add_one_leading_zero(divider_num);
}

void mantissa_offset(num_t *const structed_num, const int offset_rate)
{
    for (short int letter_ind = 0;
         letter_ind < MAX_MANTISSA_PART_LEN - 1 - offset_rate;
         ++letter_ind)
    {
        structed_num->mantissa_part[letter_ind] =
            structed_num->mantissa_part[letter_ind + offset_rate];
    }

    for (short int letter_ind = MAX_MANTISSA_PART_LEN - 1 - offset_rate;
         letter_ind < MAX_MANTISSA_PART_LEN - 1;
         ++letter_ind)
    {
        structed_num->mantissa_part[letter_ind] = '0';
    }
}