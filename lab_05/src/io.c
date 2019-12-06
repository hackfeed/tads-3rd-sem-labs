#include <stdio.h>
#include <errno.h>

#include "include/rc.h"
#include "include/macro.h"

/*
Welcomming print with available features.
*/
void welcome()
{
    printf("%s",
           ANSI_COLOR_GREEN
           " ___ _____ _   ___ _  __\n"
           "/ __|_   _/_\\ / __| |/ /\n"
           "\\__ \\ | |/ _ \\ (__| ' <\n"
           "|___/ |_/_/ \\_\\___|_|\\_\\\n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_MAGENTA
           "Данная программа позволяет сравнить время, затраченное на обработку \n"
           "стека, реализованного на основе массива и односвязного линейного списка. \n"
           "Под обработкой подразумевается вывод убывающих подпоследовательностей \n"
           "в последовательности в обратном порядке. \n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_YELLOW
           "Выберите действие из списка, введя соответствуюший номер:\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_GREEN
           "1. МАССИВ: Ввести элементы стека.\n"
           "2. МАССИВ: Добавить элемент в стек.\n"
           "3. МАССИВ: Удалить элемент из стека.\n"
           "4. МАССИВ: Вывести убывающие подпоследовательности в обратном порядке \n"
           "и вывести количественную характеристику обработки.\n"
           "5. МАССИВ: Вывести текущее состояние стека.\n\n"
           "6. СПИСОК: Ввести элементы стека.\n"
           "7. СПИСОК: Добавить элемент в стек.\n"
           "8. СПИСОК: Удалить элемент из стека.\n"
           "9. СПИСОК: Вывести массив освободившихся адрессов.\n"
           "10. СПИСОК: Вывести убывающие подпоследовательности в обратном порядке \n"
           "и вывести количественную характеристику обработки.\n"
           "11. СПИСОК: Вывести текущее состояние стека.\n\n"
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
