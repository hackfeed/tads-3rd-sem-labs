#include "defines.h"

/* Data structure for entered num. */
typedef char long_t[MAX_INT_NUM_LEN];

/* 
Data structure fo parsed num. 

* num_sign - sign of entered number (plus or minus).
* mantissa_part - part after sign and before exponent sign 
of entered number.
* order_part - part after exponent sign.
* dot_position - position number of float dot sign of 
entered number.
* exp_position - position number of exponent sign of 
entered number.
* order_int - integer representation of parsed order part.
*/
typedef struct
{
    char num_sign;
    char mantissa_part[MAX_MANTISSA_PART_LEN];
    char order_part[MAX_ORDER_PART_LEN];
    short int dot_position;
    short int exp_position;
    int order_int;
} num_t;