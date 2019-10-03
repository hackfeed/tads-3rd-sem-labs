/*
Table handling module's headers.
*/

#include "data_structures.h"

char *get_csv_field(const char *const line, int line_num);

void parse_table(const char *const filename, aio_table_t *const table);