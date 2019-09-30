/*
IO module.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../headers/data_structures.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define OK 0
#define IN_BETWEEN_ERROR 1
#define FILENAME_ERROR 2

#define MAX_FILENAME_LEN 256

#define GOT_ARG 1

/*
Welcomming print with available features.
*/
void welcome_print()
{
    system("clear");
    printf("%s",
           ANSI_COLOR_GREEN
           " ___  ___  ___ _____    ___ ___  __  __ ___  _   ___ ___\n"
           "/ __|/ _ \\| _ \\_   _|  / __/ _ \\|  \\/  | _ \\/_\\ | _ \\ __|\n"
           "\\__ \\ (_) |   / | |   | (_| (_) | |\\/| |  _/ _ \\|   / _|\n"
           "|___/\\___/|_|_\\ |_|    \\___\\___/|_|  |_|_|/_/ \\_\\_|_\\___|\n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_MAGENTA
           "Данная программа позволяет сравнить время, затраченное на сортировку таблицы\n"
           "сортировками с асимптотическими сложностями O(n^2) и O(logn); добавить в конец\n"
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
           "4. Удалить запись из таблицы.\n"
           "5. Отсортировать таблицу ключей.\n"
           "6. Вывести отсортированную исходную таблицу по количеству страниц в книге.\n"
           "7. Вывести отсортированную исходную таблицу по количеству страниц в книге,\n"
           "используя упорядоченную таблицу ключей.\n"
           "8. Вывести сравнение времени сортировки таблицы сортировками со\n"
           "сложностями O(n^2) и O(logn).\n\n"
           "0. Выход из программы." ANSI_COLOR_RESET);
}

/*
Input number in between.

Input data:
* int *const number - number of action to be done.
* const int left_border - left border of between.
* const int right_border - right border of between.

Output data:
* Return code - OK or IN_BETWEEN_ERROR.
*/
int input_number_between(int *const number, const int left_border,
                         const int right_border)
{
    scanf("%d", number);
    if (*number < left_border || *number > right_border)
    {
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
int input_filename(char filename[MAX_FILENAME_LEN])
{
    if (scanf("%s", filename) != GOT_ARG)
    {
        return FILENAME_ERROR;
    }

    return OK;
}

/*
Output main table to terminal.
*/
void output_main_table(const aio_table_t *const table)
{
    printf("┏━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━"
           "━━━━━━━━┳━━━┳━┳━━━━━━━━━━━━━━━━━━━━"
           "┳━┳━┳━━━━┳━┳━┳━┳━┳━┓\n");

    for (int record = 0; record < table->size_of_table; ++record)
    {
        printf("┃%20s┃%30s┃%25s┃%3d┃",
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

    printf("┗━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━"
           "━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━"
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