/*
IO module.
*/

#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

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
           "использования различных алгоритмов сортировки\n\n" ANSI_COLOR_RESET);
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