/*
IO module.
*/

#include <stdio.h>

#include "include/rc.h"
#include "include/macro.h"
#include "include/array.h"
#include "include/arrstack.h"
#include "include/liststack.h"

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
           "1. Ввести элементы стека.\n"
           "2. Добавить элемент в стек.\n"
           "3. Удалить элемент из стека.\n"
           "4. Вывести массив освободившихся адрессов.\n"
           "5. Вывести убывающие подпоследовательности в обратном порядке.\n\n"
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
int input_interval(int *const num, const int left, const int right)
{
    if (scanf("%d", num) != GOT_ARG)
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

/*
Input stack.

Input data:
* const int count - count of stack elements.
* arrstack_t *stack, liststack_t **root - stack realizations.
* const int limit - address limit.

Output data:
* Return code - OK or INVALID_INT_INPUT_ERROR.
*/
int input_stack(const int count, arrstack_t *stack, liststack_t **root, size_t limit)
{
    int el;

    for (int i = 0; i < count; ++i)
    {
        if (scanf("%d", &el) != GOT_ARG)
        {
            return INVALID_INT_INPUT_ERROR;
        }

        if (i == 0)
        {
            *root = create_node(el);
        }
        else
        {
            pushl(root, el, limit);
        }

        pusha(stack, el);
    }

    return OK;
}

/*
Pop element from both realizations.

Input array:
* arrstack_t *stack, liststack_t **root - stack realizations.

Output array:
* status - popped element or STACK_EMPTY status.
*/
int pop_stack(arrstack_t *stack, liststack_t **root, arr_t *const arr)
{
    int status;

    status = popa(stack);
    popl(root, arr);

    return status;
}