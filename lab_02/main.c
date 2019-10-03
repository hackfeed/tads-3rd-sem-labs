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
    char filename[MAX_FILENAME_LEN];
    while (cur_command != 0)
    {
        if (input_number_between(&cur_command, 0, 11) != OK)
        {
            printf(ANSI_COLOR_RED
                   "%s\n" ANSI_COLOR_RESET,
                   "Введена недопустимая команда! Повторите попытку");
            welcome_print();
        }

        else
        {
            if (cur_command == 1)
            {
                printf(ANSI_COLOR_YELLOW
                       "%s" ANSI_COLOR_RESET,
                       "Введите имя файла с данными: ");
                input_filename(filename);

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
        }
    }

    return 0;
}