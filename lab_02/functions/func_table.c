#include <stdio.h>
#include <string.h>

#include "../headers/data_structures.h"

#define OK 0
#define FILE_NOT_EXIST_ERROR 3
#define EMPTY_FILE_ERROR 4

char *get_csv_field(const char *const line, int line_num)
{
    char *tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n"))
    {
        if (!--line_num)
            return tok;
    }

    return NULL;
}

int parse_table(const char *const filename, aio_table_t *const table)
{
    FILE *table_file = fopen(filename, "r");

    if (!table_file)
    {
        return FILE_NOT_EXIST_ERROR;
    }

    if (fgetc(table_file) == EOF)
    {
        fseek(table_file, 0, SEEK_SET);
        return EMPTY_FILE_ERROR;
    }
}