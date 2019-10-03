/*
Table handling module.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/data_structures.h"

#define OK 0
#define FILE_NOT_EXIST_ERROR 3
#define EMPTY_FILE_ERROR 4

#define LINE_LEN 1024

/*
Parse CSV line and get field.

Input data:
* char *const line - line to be parsed.
* int field_num - num of field to be returned.

Output data:
* char *tok - pointer to field.
** NULL if nothing got.
*/
char *get_csv_field(char *const line, int field_num)
{
    char *tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n"))
    {
        if (!--field_num)
            return tok;
    }

    return NULL;
}

/*
Parse table from file to aio_table_t table.

Input data:
* const char *const filename - name of data file.
* aio_table_t *const table - table for parsing result.
*/
void parse_table(const char *const filename, aio_table_t *const table)
{
    FILE *table_file = fopen(filename, "r");

    if (!table_file)
    {
        return FILE_NOT_EXIST_ERROR;
    }

    if (fgetc(table_file) == EOF)
    {
        return EMPTY_FILE_ERROR;
    }

    fseek(table_file, 0, SEEK_SET);

    for (int record = 0; record < table->size_of_table; ++record)
    {
        char line[LINE_LEN];
        fgets(line, LINE_LEN, table_file);
        char tmp[LINE_LEN];
        strcpy(tmp, line);

        strcpy(table->main_table[record].author_last_name, get_csv_field(tmp, 1));
        strcpy(tmp, line);
        strcpy(table->main_table[record].book_name, get_csv_field(tmp, 2));
        strcpy(tmp, line);
        strcpy(table->main_table[record].publisher, get_csv_field(tmp, 3));
        strcpy(tmp, line);
        table->main_table[record].page_count = atoi(get_csv_field(tmp, 4));
        strcpy(tmp, line);
        table->main_table[record].book_type = atoi(get_csv_field(tmp, 5));

        if (table->main_table[record].book_type == technical)
        {
            strcpy(tmp, line);
            strcpy(table->main_table[record].variative_part.technical_book.field, get_csv_field(tmp, 6));
            strcpy(tmp, line);
            table->main_table[record].variative_part.technical_book.is_national = atoi(get_csv_field(tmp, 7));
            strcpy(tmp, line);
            table->main_table[record].variative_part.technical_book.is_translated = atoi(get_csv_field(tmp, 8));
            strcpy(tmp, line);
            table->main_table[record].variative_part.technical_book.release_year = atoi(get_csv_field(tmp, 9));
        }

        if (table->main_table[record].book_type == fiction)
        {
            strcpy(tmp, line);
            table->main_table[record].variative_part.fiction_book.is_novel = atoi(get_csv_field(tmp, 6));
            strcpy(tmp, line);
            table->main_table[record].variative_part.fiction_book.is_play = atoi(get_csv_field(tmp, 7));
            strcpy(tmp, line);
            table->main_table[record].variative_part.fiction_book.is_poetry = atoi(get_csv_field(tmp, 8));
        }

        if (table->main_table[record].book_type == kids)
        {
            strcpy(tmp, line);
            table->main_table[record].variative_part.kids_book.is_fairytale = atoi(get_csv_field(tmp, 6));
            strcpy(tmp, line);
            table->main_table[record].variative_part.kids_book.is_poetry = atoi(get_csv_field(tmp, 7));
        }
    }
}