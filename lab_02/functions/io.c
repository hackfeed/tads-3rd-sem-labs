/*
IO module.
*/

#include <stdio.h>
#include <string.h>

#include "../headers/data_structures.h"
#include "../headers/defines.h"

/*
Welcomming print with available features.
*/
void welcome_print()
{
    printf("%s",
           ANSI_COLOR_GREEN
           " ___  ___  ___ _____    ___ ___  __  __ ___  _   ___ ___\n"
           "/ __|/ _ \\| _ \\_   _|  / __/ _ \\|  \\/  | _ \\/_\\ | _ \\ __|\n"
           "\\__ \\ (_) |   / | |   | (_| (_) | |\\/| |  _/ _ \\|   / _|\n"
           "|___/\\___/|_|_\\ |_|    \\___\\___/|_|  |_|_|/_/ \\_\\_|_\\___|\n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_MAGENTA
           "Данная программа позволяет сравнить время, затраченное на сортировку таблицы\n"
           "сортировками с асимптотическими сложностями O(n^2) и O(nlogn); добавить в конец\n"
           "таблицы запись, введенную пользователем; удалить из таблицы запись по значению\n"
           "указанного поля; просмотреть отсортированную таблицу ключей при несортированной\n"
           "исходной таблице; вывести упорядоченную исходную таблицу; вывести исходную таблицу\n"
           "в упорядоченном виде, используя упорядоченную таблицу ключей; вывести результаты\n"
           "использования различных алгоритмов сортировки.\n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_YELLOW
           "Выберите действие из списка, введя соответствуюший номер:\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_GREEN
           "1. Выгрузить таблицу из файла.\n"
           "2. Вывести на экран выгруженную таблицу.\n"
           "3. Добавить запись в таблицу.\n"
           "4. Удалить запись из таблицы по количеству страниц книги.\n"
           "5. Отсортировать таблицу ключей сортировкой O(n^2).\n"
           "6. Отсортировать таблицу ключей сортировкой O(nlogn).\n"
           "7. Вывести таблицу ключей.\n"
           "8. Отсортировать исходную таблицу по количеству страниц в книге сортировкой O(n^2).\n"
           "9. Отсортировать исходную таблицу по количеству страниц в книге сортировкой O(nlogn).\n"
           "10. Вывести исходную таблицу, используя упорядоченную таблицу ключей.\n"
           "11. Вывести сравнение времени сортировки таблицы сортировками со\n"
           "сложностями O(n^2) и O(nlogn) и сравнение времени обычной сортировки и сортировки с использованием\n"
           "массива ключей.\n"
           "12. Вывести список отечетвенной технической литературы по указанной области.\n\n"
           "0. Выход из программы.\n\n" ANSI_COLOR_RESET);
}

/*
Clean input stream from trash.
*/
void clean_input_stream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

/*
Input number in between.

Input data:
* int *const number - number of action to be done.
* const int left_border - left border of between.
* const int right_border - right border of between.

Output data:
* Return code - OK, INVALID_INT_INPUT_ERROR or IN_BETWEEN_ERROR.
*/
int input_number_between(int *const number, const int left_border,
                         const int right_border)
{
    if (scanf("%d", number) != GOT_ARG)
    {
        clean_input_stream();
        return INVALID_INT_INPUT_ERROR;
    }

    if (*number < left_border || *number > right_border)
    {
        clean_input_stream();
        return IN_BETWEEN_ERROR;
    }

    return OK;
}

/*
Input filename for data file.

Input data:
* char filename[MAX_FILENAME_LEN] - array to store filename.

Output data:
* Return code - OK of FILENAME_ERROR.
*/
int input_string(char *stringname)
{
    if (scanf("%s", stringname) != GOT_ARG)
    {
        clean_input_stream();
        return STRINGNAME_ERROR;
    }

    return OK;
}

/*
Output main table to terminal.
*/
void output_main_table(const aio_table_t *const table)
{
    printf("┏━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━┳━━━┳━┳━━━━━━━━━━━━━━━━━━━━"
           "┳━┳━┳━━━━┳━┳━┳━┳━┳━┓\n");

    for (int record = 0; record < table->size_of_table; ++record)
    {
        printf("┃%20s┃%43s┃%38s┃%3d┃",
               table->main_table[record].author_last_name,
               table->main_table[record].book_name,
               table->main_table[record].publisher,
               table->main_table[record].page_count);

        if (table->main_table[record].book_type == technical)
        {
            printf("%1d┃%20s┃%1d┃%1d┃%4d┃ ┃ ┃ ┃ ┃ ┃\n",
                   table->main_table[record].book_type,
                   table->main_table[record].variative_part.technical_book.field,
                   table->main_table[record].variative_part.technical_book.is_national,
                   table->main_table[record].variative_part.technical_book.is_translated,
                   table->main_table[record].variative_part.technical_book.release_year);
        }

        if (table->main_table[record].book_type == fiction)
        {
            printf("%1d┃                    ┃ ┃ ┃    ┃%1d┃%1d┃%1d┃ ┃ ┃\n",
                   table->main_table[record].book_type,
                   table->main_table[record].variative_part.fiction_book.is_novel,
                   table->main_table[record].variative_part.fiction_book.is_play,
                   table->main_table[record].variative_part.fiction_book.is_poetry);
        }

        if (table->main_table[record].book_type == kids)
        {
            printf("%1d┃                    ┃ ┃ ┃    ┃ ┃ ┃ ┃%1d┃%1d┃\n",
                   table->main_table[record].book_type,
                   table->main_table[record].variative_part.fiction_book.is_novel,
                   table->main_table[record].variative_part.fiction_book.is_play,
                   table->main_table[record].variative_part.fiction_book.is_poetry);
        }
    }

    printf("┗━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━┻━━━┻━┻━━━━━━━━━━━━━━━━━━━━"
           "┻━┻━┻━━━━┻━┻━┻━┻━┻━┛\n");
}

/*
Output key table to terminal.
*/
void output_key_table(const aio_table_t *const table)
{
    printf("┏━━━┳━━━┓\n");

    for (int record = 0; record < table->size_of_table; ++record)
    {
        printf("┃%3d┃%3d┃\n",
               table->key_table[record].book_table_index,
               table->key_table[record].page_count);
    }

    printf("┗━━━┻━━━┛\n");
}

/*
Output main table by key table to terminal.
*/
void output_main_by_key(const aio_table_t *const table)
{
    printf("┏━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━┳━━━┳━┳━━━━━━━━━━━━━━━━━━━━"
           "┳━┳━┳━━━━┳━┳━┳━┳━┳━┓\n");

    for (int record = 0; record < table->size_of_table; ++record)
    {
        printf("┃%20s┃%43s┃%38s┃%3d┃",
               table->main_table[table->key_table[record].book_table_index].author_last_name,
               table->main_table[table->key_table[record].book_table_index].book_name,
               table->main_table[table->key_table[record].book_table_index].publisher,
               table->main_table[table->key_table[record].book_table_index].page_count);

        if (table->main_table[table->key_table[record].book_table_index].book_type == technical)
        {
            printf("%1d┃%20s┃%1d┃%1d┃%4d┃ ┃ ┃ ┃ ┃ ┃\n",
                   table->main_table[table->key_table[record].book_table_index].book_type,
                   table->main_table[table->key_table[record].book_table_index].variative_part.technical_book.field,
                   table->main_table[table->key_table[record].book_table_index].variative_part.technical_book.is_national,
                   table->main_table[table->key_table[record].book_table_index].variative_part.technical_book.is_translated,
                   table->main_table[table->key_table[record].book_table_index].variative_part.technical_book.release_year);
        }

        if (table->main_table[table->key_table[record].book_table_index].book_type == fiction)
        {
            printf("%1d┃                    ┃ ┃ ┃    ┃%1d┃%1d┃%1d┃ ┃ ┃\n",
                   table->main_table[table->key_table[record].book_table_index].book_type,
                   table->main_table[table->key_table[record].book_table_index].variative_part.fiction_book.is_novel,
                   table->main_table[table->key_table[record].book_table_index].variative_part.fiction_book.is_play,
                   table->main_table[table->key_table[record].book_table_index].variative_part.fiction_book.is_poetry);
        }

        if (table->main_table[table->key_table[record].book_table_index].book_type == kids)
        {
            printf("%1d┃                    ┃ ┃ ┃    ┃ ┃ ┃ ┃%1d┃%1d┃\n",
                   table->main_table[table->key_table[record].book_table_index].book_type,
                   table->main_table[table->key_table[record].book_table_index].variative_part.fiction_book.is_novel,
                   table->main_table[table->key_table[record].book_table_index].variative_part.fiction_book.is_play,
                   table->main_table[table->key_table[record].book_table_index].variative_part.fiction_book.is_poetry);
        }
    }

    printf("┗━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━┻━━━┻━┻━━━━━━━━━━━━━━━━━━━━"
           "┻━┻━┻━━━━┻━┻━┻━┻━┻━┛\n");
}

/*
Output table by user-defined techfield.
*/
void output_table_by_techfield(const aio_table_t *const table,
                               char needed_field[MAX_STRING_FIELD_SIZE])
{
    printf("┏━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━┳━━━┳━┳━━━━━━━━━━━━━━━━━━━━"
           "┳━┳━┳━━━━┳━┳━┳━┳━┳━┓\n");

    for (int record = 0; record < table->size_of_table; ++record)
    {
        if (table->main_table[record].book_type == technical &&
            table->main_table[record].variative_part.technical_book.is_national == 1 &&
            strcmp(table->main_table[record].variative_part.technical_book.field,
                   needed_field) == GOT_IDENTITY)
        {
            printf("┃%20s┃%43s┃%38s┃%3d┃",
                   table->main_table[record].author_last_name,
                   table->main_table[record].book_name,
                   table->main_table[record].publisher,
                   table->main_table[record].page_count);

            printf("%1d┃%20s┃%1d┃%1d┃%4d┃ ┃ ┃ ┃ ┃ ┃\n",
                   table->main_table[record].book_type,
                   table->main_table[record].variative_part.technical_book.field,
                   table->main_table[record].variative_part.technical_book.is_national,
                   table->main_table[record].variative_part.technical_book.is_translated,
                   table->main_table[record].variative_part.technical_book.release_year);
        }
    }

    printf("┗━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
           "━━━━━━━━┻━━━┻━┻━━━━━━━━━━━━━━━━━━━━"
           "┻━┻━┻━━━━┻━┻━┻━┻━┻━┛\n");
}