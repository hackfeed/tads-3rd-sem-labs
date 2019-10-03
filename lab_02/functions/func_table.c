#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/data_structures.h"

#define OK 0
#define FILE_NOT_EXIST_ERROR 3
#define EMPTY_FILE_ERROR 4

#define LINE_LEN 1024

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

    for (int record = 0; record < table->size_of_table; ++record)
    {
        char line[LINE_LEN];
        fgets(line, LINE_LEN, table_file);

        char *tmp = strdup(line);
        srtcpy(table->main_table[record].author_last_name, get_csv_field(tmp, 0));
        tmp = strdup(line);
        srtcpy(table->main_table[record].book_name, get_csv_field(tmp, 1));
        tmp = strdup(line);
        srtcpy(table->main_table[record].publisher, get_csv_field(tmp, 2));
        tmp = strdup(line);
        table->main_table[record].page_count = atoi(get_csv_field(tmp, 3));
        tmp = strdup(line);
        table->main_table[record].book_type = atoi(get_csv_field(tmp, 4));

        if (table->main_table[record].book_type == technical)
        {
            tmp = strdup(line);
            strcpy(table->main_table[record].variative_part.technical_book.field, get_csv_field(tmp, 5));
        }
    }
}