/*
Return codes, integer constants and 
boolean constants definition.
*/

#define OK 0

#define PARSE_ERROR 1
#define SIGN_PARSE_ERROR 2
#define DOT_PARSE_ERROR 3
#define MANTISSA_PARSE_ERROR 4
#define ORDER_PARSE_ERROR 5

#define VALIDATION_ERROR 6
#define MANTISSA_VALIDATION_ERROR 7
#define ORDER_SIGN_VALIDATION_ERROR 8
#define ORDER_VALIDATION_ERROR 9

#define TYPE_INT 10
#define TYPE_FLOAT 11

#define MAX_MANTISSA_PART_LEN 32
#define MAX_INT_NUM_LEN 30
#define MAX_LONG_T_NUM_LEN 40
#define MAX_ORDER_PART_LEN 7

#define TRUE 1
#define FALSE 0
#define POSITIVE '+'
#define NEGATIVE '-'
#define NONE 'N'