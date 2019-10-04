/*
IO module headers.
*/

#ifndef __IO_H__
#define __IO_H__

#include "data_structures.h"
#include "defines.h"

void welcome_print();

void clean_input_stream();

int input_number_between(int *const number, const int left_border, const int right_border);

int input_string(char *const stringname[MAX_STRING_FIELD_SIZE]);

void output_main_table(const aio_table_t *const table);

void output_key_table(const aio_table_t *const table);

void output_main_by_key(const aio_table_t *const table);

void output_table_by_techfield(const aio_table_t *const table, char needed_field[MAX_STRING_FIELD_SIZE]);

#endif