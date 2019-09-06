#include "defines.h"

typedef char long_t[MAX_INT_NUM_LEN];

typedef struct
{
    char num_sign;
    char mantissa_part[MAX_MANTISSA_PART_LEN];
    short int dot_position;
    short int exp_position;
    int order_part;
} num_t;