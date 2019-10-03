/*
Table handling module's headers.
*/

#ifndef __FUNC_TABLE_H__
#define __FUNC_TABLE_H__

#include "data_structures.h"

char *get_csv_field(const char *const line, int line_num);

void parse_table(const char *const filename, aio_table_t *const table);

int add_record(aio_table_t *const table);

#endif