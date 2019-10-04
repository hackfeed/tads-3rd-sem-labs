#include <stdio.h>
#include <stdlib.h>
#include "headers/io.h"
#include "headers/func_table.h"

int main()
{
    book_t main_table[350];
    book_key_t key_table[350];

    aio_table_t table;
    table.main_table = main_table;
    table.key_table = key_table;
    table.size_of_table = 300;

    system("clear");
    welcome_print();

    int cur_command = -1;
    boolean_t is_downloaded = FALSE;
    char filename[MAX_STRING_FIELD_SIZE];

    while (cur_command != 0)
    {
        if (input_number_between(&cur_command, 0, 12) != OK)
        {
            printf(ANSI_COLOR_RED
                   "%s\n" ANSI_COLOR_RESET,
                   "Введена недопустимая команда! Повторите попытку.");

            welcome_print();
        }

        else
        {
            if (cur_command == 1)
            {
                printf(ANSI_COLOR_YELLOW
                       "%s" ANSI_COLOR_RESET,
                       "Введите имя файла с данными: ");
                input_string(filename);

                int parse_res = parse_table(filename, &table);
                if (parse_res == FILE_NOT_EXIST_ERROR || parse_res == EMPTY_FILE_ERROR)
                {
                    is_downloaded = FALSE;

                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Ошибка файла! Файл не сущесвтует или пустой!");
                }

                else
                {
                    is_downloaded = TRUE;

                    printf(ANSI_COLOR_GREEN
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл успешно выгружен!");
                }

                welcome_print();
            }

            if (cur_command == 2)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    output_main_table(&table);
                }

                welcome_print();
            }

            if (cur_command == 3)
            {
                if (table.size_of_table == 350)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Достигнут максимальный размер таблицы!");
                }

                else
                {
                    int add_res = add_record(&table);

                    if (is_downloaded == FALSE)
                    {
                        printf(ANSI_COLOR_RED
                               "%s\n" ANSI_COLOR_RESET,
                               "Файл не выгружен! Таблица пуста!");
                    }

                    else
                    {
                        if (add_res == INVALID_STRING_INPUT_ERROR)
                        {
                            printf(ANSI_COLOR_RED
                                   "%s\n" ANSI_COLOR_RESET,
                                   "Введено неверное строковое поле!");
                        }

                        if (add_res == INVALID_INT_INPUT_ERROR)
                        {
                            printf(ANSI_COLOR_RED
                                   "%s\n" ANSI_COLOR_RESET,
                                   "Введено число, выходящее за допустимый интервал!");
                        }

                        if (add_res == MULTIPLE_GENRES_ERROR)
                        {
                            printf(ANSI_COLOR_RED
                                   "%s\n" ANSI_COLOR_RESET,
                                   "Логическое поле может быть истинно только в одном случае!");
                        }

                        if (add_res == OK)
                        {
                            printf(ANSI_COLOR_GREEN
                                   "%s\n" ANSI_COLOR_RESET,
                                   "Запись успешно добавлена!");
                        }
                    }
                }

                welcome_print();
            }

            if (cur_command == 4)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    printf(ANSI_COLOR_YELLOW
                           "%s" ANSI_COLOR_RESET,
                           "Введите количество страниц, по которому "
                           "нужно удалить записи: ");

                    int pages_count;
                    if (input_number_between(&pages_count, 1, 999) != OK)
                    {
                        printf(ANSI_COLOR_RED
                               "%s\n" ANSI_COLOR_RESET,
                               "Введено недопустимое количество страниц!");
                    }

                    else
                    {
                        int deletions_count = delete_record_by_pages(&table, &pages_count);

                        printf(ANSI_COLOR_GREEN
                               "%s%d%s\n" ANSI_COLOR_RESET,
                               "Удалено(-а) ", deletions_count, " записей(-ь)");
                    }
                }

                welcome_print();
            }

            if (cur_command == 5)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    uint64_t start, end;

                    start = tick();
                    bubble_sort_table(&table, FALSE);
                    end = tick();

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время сортировки таблицы ключей"
                           " при помощи сортировки пузырьком = ",
                           end - start);
                }

                welcome_print();
            }

            if (cur_command == 6)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    uint64_t start, end;

                    start = tick();
                    quick_sort_table(&table, FALSE, 0, table.size_of_table - 1);
                    end = tick();

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время сортировки таблицы ключей"
                           " при помощи быстрой сортировки = ",
                           end - start);
                }

                welcome_print();
            }

            if (cur_command == 7)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    output_key_table(&table);
                }

                welcome_print();
            }

            if (cur_command == 8)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    uint64_t start, end;

                    start = tick();
                    bubble_sort_table(&table, TRUE);
                    output_main_table(&table);
                    end = tick();

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время сортировки и вывода основной таблицы"
                           " при помощи сортировки пузырьком = ",
                           end - start);
                }

                welcome_print();
            }

            if (cur_command == 9)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    uint64_t start, end;

                    start = tick();
                    quick_sort_table(&table, TRUE, 0, table.size_of_table - 1);
                    output_main_table(&table);
                    end = tick();

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время сортировки и вывода основной таблицы"
                           " при помощи быстрой сортировки = ",
                           end - start);
                }

                welcome_print();
            }

            if (cur_command == 10)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    uint64_t start, end;

                    start = tick();
                    quick_sort_table(&table, FALSE, 0, table.size_of_table - 1);
                    output_main_by_key(&table);
                    end = tick();

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время вывода основной таблицы"
                           " при помощи таблицы ключей = ",
                           end - start);
                }

                welcome_print();
            }

            if (cur_command == 11)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    uint64_t start, end;
                    uint64_t result_bubble, result_quick, result_by_key;

                    parse_table(filename, &table);
                    start = tick();
                    bubble_sort_table(&table, TRUE);
                    output_main_table(&table);
                    end = tick();
                    result_bubble = start - end;

                    parse_table(filename, &table);
                    start = tick();
                    quick_sort_table(&table, TRUE, 0, table.size_of_table - 1);
                    output_main_table(&table);
                    end = tick();
                    result_quick = start - end;

                    parse_table(filename, &table);
                    start = tick();
                    quick_sort_table(&table, FALSE, 0, table.size_of_table - 1);
                    output_main_by_key(&table);
                    end = tick();
                    result_by_key = start - end;

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время сортировки и вывода основной таблицы"
                           " при помощи сортировки пузырьком = ",
                           result_bubble);

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время сортировки и вывода основной таблицы"
                           " при помощи быстрой сортировки   = ",
                           result_quick);

                    printf(ANSI_COLOR_GREEN
                           "%s%ju\n" ANSI_COLOR_RESET,
                           "Время вывода основной таблицы"
                           " при помощи таблицы ключей                    = ",
                           result_by_key);
                }

                welcome_print();
            }

            if (cur_command == 12)
            {
                if (is_downloaded == FALSE)
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Файл не выгружен! Таблица пуста!");
                }

                else
                {
                    char field_to_find[MAX_STRING_FIELD_SIZE];

                    printf(ANSI_COLOR_YELLOW
                           "%s" ANSI_COLOR_RESET,
                           "Введите отрасль технического труда: ");
                    input_string(field_to_find);

                    output_table_by_techfield(&table, field_to_find);
                }

                welcome_print();
            }
        }
    }

    return OK;
}