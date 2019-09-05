#define MAX_MANTISSA_PART_LEN 33
#define MAX_INT_NUM_LEN 31
#define POSITIVE '+'
#define NEGATIVE '-'

typedef char long_t[MAX_INT_NUM_LEN];

typedef struct
{
    char num_sign = NEGATIVE;
    char mantissa_part[MAX_MANTISSA_PART_LEN];
    short int dot_position;
    short int exp_position;
    int order_part;
} num_t;