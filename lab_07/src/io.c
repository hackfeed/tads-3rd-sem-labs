#include "include/io.h"

/*
Welcomming print with available features.
*/
void welcome()
{
    printf("%s",
           ANSI_COLOR_GREEN
           "_____________________________________  __\n"
           "__  ____/__  __ \\__    |__  __ \\__  / / /\n"
           "_  / __ __  /_/ /_  /| |_  /_/ /_  /_/ / \n"
           "/ /_/ / _  _, _/_  ___ |  ____/_  __  /  \n"
           "\\____/  /_/ |_| /_/  |_/_/     /_/ /_/   \n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_MAGENTA
           "Данная программа позволяет смоделировать поиск минимального по количеству \n"
           "ребер подмножества ребер, удаление которого превращает заданный граф в несвязный. \n\n" ANSI_COLOR_RESET);
}

/*
Clean input stream from trash.
*/
void clinstream()
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
int rnginput(int *const num, const int left, const int right)
{
    if (scanf("%d", num) != GOT_ARG)
    {
        clinstream();
        return EINVALIDINTEGER;
    }

    if (*num < left || *num > right)
    {
        clinstream();
        return EINVALIDRANGE;
    }

    return EOK;
}
