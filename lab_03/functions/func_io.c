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
void welcome()
{
    printf("%s",
           ANSI_COLOR_GREEN
           " ___ ___  _   ___  ___ ___   __  __   _ _____ ___ _____  __\n"
           "/ __| _ \\/_\\ | _ \\/ __| __| |  \\/  | /_\\_   _| _ \\_ _\\ \\/ /\n"
           "\\__ \\  _/ _ \\|   /\\__ \\ _|  | |\\/| |/ _ \\| | |   /| | >  <\n"
           "|___/_|/_/ \\_\\_|_\\|___/___| |_|  |_/_/ \\_\\_| |_|_\\___/_/\\_\\\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_MAGENTA
           "Данная программа позволяет сравнить время, затраченное на сложение \n"
           "двух разреженных матриц, хранимых в стандартном виде и в виде хранения \n"
           "по столбцам.\n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_YELLOW
           "Выберите действие из списка, введя соответствуюший номер:\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_GREEN
           "1. Ввести матрицы вручную (в формате Matrix Market).\n"
           "2. Сгенерировать матрицы случайно (по проценту заполненности).\n"
           "3. Сложить матрицы, используя стандартный способ хранения.\n"
           "4. Сложить матрицы, используя способ хранения по столбцам.\n\n"
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

Output data:
* Return code - OK, INVALID_INT_INPUT_ERROR or IN_BETWEEN_ERROR.
*/
int input_interval(type_t *const num, const type_t left, const type_t right)
{
    if (scanf(type_spec, num) != GOT_ARG)
    {
        clean_input_stream();
        return INVALID_INT_INPUT_ERROR;
    }

    if (*num < left || *num > right)
    {
        clean_input_stream();
        return INVALID_INTERVAL_ERROR;
    }

    return OK;
}