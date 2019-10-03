/*
IO module headers.
*/

#include "data_structures.h"

#define MAX_FILENAME_LEN 256

void welcome_print();

int input_number_between(int *const number, const int left_border, const int right_border);

int input_filename(char filename[MAX_FILENAME_LEN]);

void output_main_table(const aio_table_t *const table);

void output_key_table(const aio_table_t *const table);