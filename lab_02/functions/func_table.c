/*
Table handling module.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/data_structures.h"
#include "../headers/defines.h"
#include "../headers/io.h"

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
int parse_table(const char *const filename, aio_table_t *const table)
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
        char line[MAX_STRING_FIELD_SIZE];
        fgets(line, MAX_STRING_FIELD_SIZE, table_file);
        char tmp[MAX_STRING_FIELD_SIZE];
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

        table->key_table[record].book_table_index = record;
        strcpy(tmp, line);
        table->key_table[record].page_count = atoi(get_csv_field(tmp, 4));

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

    fclose(table_file);

    return OK;
}

/*
Add record to the table.

Input data:
* aio_table_t *const table - table to be modified.

Output data:
* Return code - OK, INVALID_STRING_INPUT_ERROR, INVALID_INT_INPUT_ERROR
or MULTIPLE_GENRES_ERROR.
*/
int add_record(aio_table_t *const table)
{
    book_t new_record;

    printf(ANSI_COLOR_MAGENTA
           "ПРИ ВВОДЕ ТЕКСТОВЫХ ЗНАЧЕНИЙ "
           "ВВОД МНОГОСЛОВНЫХ ЗНАЧЕНИЙ ОСУЩЕСТВЛЯТЬ ЧЕРЕЗ СИМВОЛ '_'\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
           "Введите фамилию автора (в английской раскладке): ");
    if (scanf("%s", new_record.author_last_name) != GOT_ARG)
    {
        return INVALID_STRING_INPUT_ERROR;
    }

    printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
           "Введите название книги (в английской раскладке): ");
    if (scanf("%s", new_record.book_name) != GOT_ARG)
    {
        return INVALID_STRING_INPUT_ERROR;
    }

    printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
           "Введите издателя (в английской раскладке): ");
    if (scanf("%s", new_record.publisher) != GOT_ARG)
    {
        return INVALID_STRING_INPUT_ERROR;
    }

    printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
           "Введите количество страниц (от 1 до 999): ");
    if (input_number_between(&new_record.page_count, 1, 999) != OK)
    {
        return INVALID_INT_INPUT_ERROR;
    }

    printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
           "Введите тип литературы от 1 до 3 (1 - техническая, "
           "2 - художественная, 3 - детская): ");
    if (input_number_between(&new_record.book_type, 1, 3) != OK)
    {
        return INVALID_INT_INPUT_ERROR;
    }

    if (new_record.book_type == technical)
    {
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Введите отрасль данной книги:");
        if (scanf("%s", new_record.variative_part.technical_book.field) != GOT_ARG)
        {
            return INVALID_STRING_INPUT_ERROR;
        }

        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Является ли данная книга отечественной (1 - да, 0 - нет):");
        if (input_number_between(&new_record.variative_part.technical_book.is_national, 0, 1) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Является ли данная книга переведенной (1 - да, 0 - нет):");
        if (input_number_between(&new_record.variative_part.technical_book.is_translated, 0, 1) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Введите год издания данной книги:");
        if (input_number_between(&new_record.variative_part.technical_book.release_year, 1, 2019) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }
    }

    if (new_record.book_type == fiction)
    {
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Является ли данная книга романом (1 - да, 0 - нет):");
        if (input_number_between(&new_record.variative_part.fiction_book.is_novel, 0, 1) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Является ли данная книга пьесой (1 - да, 0 - нет):");
        if (input_number_between(&new_record.variative_part.fiction_book.is_play, 0, 1) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Является ли данная книга сборником стихов (1 - да, 0 - нет):");
        if (input_number_between(&new_record.variative_part.fiction_book.is_poetry, 0, 1) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        if (new_record.variative_part.fiction_book.is_novel == TRUE)
        {
            if (new_record.variative_part.fiction_book.is_play == TRUE ||
                new_record.variative_part.fiction_book.is_poetry == TRUE)
            {
                return MULTIPLE_GENRES_ERROR;
            }
        }

        if (new_record.variative_part.fiction_book.is_play == TRUE)
        {
            if (new_record.variative_part.fiction_book.is_novel == TRUE ||
                new_record.variative_part.fiction_book.is_poetry == TRUE)
            {
                return MULTIPLE_GENRES_ERROR;
            }
        }

        if (new_record.variative_part.fiction_book.is_poetry == TRUE)
        {
            if (new_record.variative_part.fiction_book.is_play == TRUE ||
                new_record.variative_part.fiction_book.is_novel == TRUE)
            {
                return MULTIPLE_GENRES_ERROR;
            }
        }

        if (new_record.variative_part.fiction_book.is_novel == FALSE &&
            new_record.variative_part.fiction_book.is_play == FALSE &&
            new_record.variative_part.fiction_book.is_poetry == FALSE)
        {
            return MULTIPLE_GENRES_ERROR;
        }
    }

    if (new_record.book_type == kids)
    {
        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Является ли данная книга сборником сказок (1 - да, 0 - нет):");
        if (input_number_between(&new_record.variative_part.kids_book.is_fairytale, 0, 1) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
               "Является ли данная книга сборником стихов (1 - да, 0 - нет):");
        if (input_number_between(&new_record.variative_part.kids_book.is_poetry, 0, 1) != OK)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        if (new_record.variative_part.kids_book.is_fairytale == TRUE &&
                new_record.variative_part.kids_book.is_poetry == TRUE ||
            new_record.variative_part.kids_book.is_fairytale == FALSE &&
                new_record.variative_part.kids_book.is_poetry == FALSE)
        {
            return MULTIPLE_GENRES_ERROR;
        }
    }

    table->main_table[table->size_of_table] = new_record;
    table->key_table[table->size_of_table].book_table_index = table->size_of_table;
    table->key_table[table->size_of_table].page_count = new_record.page_count;
    table->size_of_table++;

    return OK;
}

/*
Delete records in table by specified page count.

Input data:
* aio_table_t *const table - table to be modified.
* const int *const pages - page count which will be removed.

Output data:
* int deletions_count - amout of deleted records.
*/
int delete_record_by_pages(aio_table_t *const table, const int *const pages)
{
    int deletions_count = 0;

    for (int record = 0; record < table->size_of_table; ++record)
    {
        if (table->main_table[record].page_count == *pages)
        {
            for (int record_offset = record;
                 record_offset < table->size_of_table - 1;
                 ++record_offset)
            {
                table->main_table[record_offset] = table->main_table[record_offset + 1];
                table->key_table[record_offset] = table->key_table[record_offset + 1];
            }

            deletions_count++;
            record--;
            table->size_of_table--;
        }
    }

    return deletions_count;
}

/*
Quick sort implementation for aio_table_t.

Input data:
* aio_table_t *const table - table to be sorted.
* const boolean_t table_to_sort - sign which table should 
be sorted (TRUE - main_table, FALSE - key_table).
* const int first, const int last - first and last indexes.
*/
void quick_sort_table(aio_table_t *const table, const boolean_t table_to_sort,
                      const int first, const int last)
{
    if (table_to_sort == TRUE)
    {
        unsigned int i, j, pivot;
        book_t first_record, last_record, pivot_record;

        if (first < last)
        {
            pivot = (first + last) / 2;
            i = first;
            j = last;

            while (i < j)
            {
                first_record = table->main_table[i];
                last_record = table->main_table[j];
                pivot_record = table->main_table[pivot];

                while (first_record.page_count <= pivot_record.page_count && i < last)
                {
                    i++;
                    first_record = table->main_table[i];
                }

                while (last_record.page_count > pivot_record.page_count)
                {
                    j--;
                    last_record = table->main_table[j];
                }

                if (i < j)
                {
                    table->main_table[i] = last_record;
                    table->main_table[j] = first_record;
                }
            }

            table->main_table[pivot] = last_record;
            table->main_table[j] = pivot_record;

            quick_sort_table(table, 1, first, i - 1);
            quick_sort_table(table, 1, j + 1, last);
        }
    }

    if (table_to_sort == FALSE)
    {
        unsigned int i, j, pivot;
        book_key_t first_record, last_record, pivot_record;

        if (first < last)
        {
            pivot = (first + last) / 2;
            i = first;
            j = last;

            while (i < j)
            {
                first_record = table->key_table[i];
                last_record = table->key_table[j];
                pivot_record = table->key_table[pivot];

                while (first_record.page_count <= pivot_record.page_count && i < last)
                {
                    i++;
                    first_record = table->key_table[i];
                }

                while (last_record.page_count > pivot_record.page_count)
                {
                    j--;
                    last_record = table->key_table[j];
                }

                if (i < j)
                {
                    table->key_table[i] = last_record;
                    table->key_table[j] = first_record;
                }
            }

            table->key_table[pivot] = last_record;
            table->key_table[j] = pivot_record;

            quick_sort_table(table, 0, first, i - 1);
            quick_sort_table(table, 0, j + 1, last);
        }
    }
}

/*
Bubble sort implementation for aio_table_t.

Input data:
* aio_table_t *const table - table to be sorted.
* const boolean_t table_to_sort - sign which table should 
be sorted (TRUE - main_table, FALSE - key_table).
*/
void bubble_sort_table(aio_table_t *const table, const boolean_t table_to_sort)
{
    if (table_to_sort == TRUE)
    {
        for (int record = 0; record < table->size_of_table; ++record)
        {
            for (int record_offset = 0;
                 record_offset < table->size_of_table - 1;
                 ++record_offset)
            {
                if (table->main_table[record_offset].page_count >
                    table->main_table[record_offset + 1].page_count)
                {
                    book_t tmp = table->main_table[record_offset];
                    table->main_table[record_offset] = table->main_table[record_offset + 1];
                    table->main_table[record_offset + 1] = tmp;
                }
            }
        }
    }

    if (table_to_sort == FALSE)
    {
        for (int record = 0; record < table->size_of_table; ++record)
        {
            for (int record_offset = 0;
                 record_offset < table->size_of_table - 1;
                 ++record_offset)
            {
                if (table->key_table[record_offset].page_count >
                    table->key_table[record_offset + 1].page_count)
                {
                    book_key_t tmp = table->key_table[record_offset];
                    table->key_table[record_offset] = table->key_table[record_offset + 1];
                    table->key_table[record_offset + 1] = tmp;
                }
            }
        }
    }
}