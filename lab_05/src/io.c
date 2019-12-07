#include "include/io.h"

/*
Welcomming print with available features.
*/
void welcome()
{
    printf("%s",
           ANSI_COLOR_GREEN
           "   ____                       \n"
           "  /___ \\_   _  ___ _   _  ___ \n"
           " //  / / | | |/ _ \\ | | |/ _ \\\n"
           "/ \\_/ /| |_| |  __/ |_| |  __/\n"
           "\\___,_\\ \\__,_|\\___|\\__,_|\\___|\n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_MAGENTA
           "Данная программа позволяет сравнить время, затраченное на обработку \n"
           "очереди, реализованной на основе массива и односвязного линейного списка. \n"
           "Под обработкой подразумевается обработка деятельности обслуживающего аппарата. \n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_YELLOW
           "Выберите действие из списка, введя соответствуюший номер:\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_GREEN
           "1. МАССИВ: Ввести данные обслуживающего аппарата и вывести статистику работы.\n"
           "2. МАССИВ: Вывести количественную характеристику выполнения операций над очередью.\n\n"
           "3. СПИСОК: Ввести данные обслуживающего аппарата и вывести статистику работы.\n"
           "4. СПИСОК: Вывести количественную характеристику выполнения операций над очередью.\n\n"
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
* int *const num - number of action to be done.
* const int left - left border of between.
* const int right - right border of between.
*/
void input_interval(int *const num, const int left, const int right)
{
    if (scanf("%d", num) != GOT_ARG)
    {
        clean_input_stream();
        errno = EINVALIDINTINPUT;
        return;
    }

    if (*num < left || *num > right)
    {
        clean_input_stream();
        errno = EINVALIDINTER;
        return;
    }
}
