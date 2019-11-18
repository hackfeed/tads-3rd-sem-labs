#include <stdio.h>
#include <inttypes.h>

#include "include/rc.h"
#include "include/macro.h"
#include "include/array.h"
#include "include/arrstack.h"
#include "include/liststack.h"
#include "include/io.h"
#include "include/stackops.h"

int main()
{
    size_t limit;
    int capacity, max_capacity;
    arr_t *fmem = NULL;
    liststack_t *root = NULL;
    arrstack_t *stack = NULL;

    int cmd = -1;

    welcome();

    while (cmd)
    {
        if (input_interval(&cmd, 0, 5))
        {
            printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                   "Введена недопустимая команда! Повторите попытку.");

            welcome();
        }

        else
        {
            if (cmd == 1)
            {
                if (fmem || stack || root)
                {
                    printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                           "Стек уже существует! Выход из программы..");

                    free_stacka(stack);
                    free_stackl(&root, fmem);
                    free_array(fmem);

                    return OK;
                }
                else
                {
                    printf("%s\n", "Введите максимальное число элементов в стеке:");
                    if (input_interval(&max_capacity, 0, INT8_MAX))
                    {
                        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                               "Введено недопустимое значение! Повторите попытку.");

                        return OK;
                    }

                    printf("%s\n", "Введите максимальный допустимый адрес (в 16-ричной форме):");
                    if (scanf("%zx", &limit) != GOT_ARG)
                    {
                        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                               "Введено недопустимое значение! Повторите попытку.");

                        return OK;
                    }

                    printf("%s\n", "Введите начальное число элементов в стеке:");
                    if (input_interval(&capacity, 0, max_capacity))
                    {
                        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                               "Введено недопустимое значение! Повторите попытку.");

                        return OK;
                    }

                    stack = create_stacka(max_capacity);
                    fmem = create_array(max_capacity);

                    printf("%s\n", "Введите элементы стека (целые числа):");
                    if (input_stack(capacity, stack, &root, limit))
                    {
                        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                               "Введено недопустимое значение! Повторите попытку.");

                        free_stacka(stack);
                        free_stackl(&root, fmem);
                        free_array(fmem);

                        return OK;
                    }

                    printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
                           "Стек успешно заполнен.");
                }

                welcome();
            }

            if (cmd == 2)
            {
                printf("%s\n", "Введите элемент для добавления в стек:");
                if (is_fulla(stack))
                {
                    printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                           "Размер стека достиг максимального значения!");
                }
                else
                {
                    if (input_stack(1, stack, &root, limit))
                    {
                        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                               "Введено недопустимое значение! Повторите попытку.");

                        free_stacka(stack);
                        free_stackl(&root, fmem);
                        free_array(fmem);

                        return OK;
                    }

                    printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
                           "Значение успешно помещено в стек.");
                }

                welcome();
            }

            if (cmd == 3)
            {
                if (is_emptya(stack))
                {
                    printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET,
                           "Стек пуст!");
                }
                else
                {
                    int popped = pop_stack(stack, &root, fmem);
                    if (popped != STACK_EMPTY)
                    {
                        printf(ANSI_COLOR_GREEN "%s%d\n" ANSI_COLOR_RESET,
                               "Значение успешно извлечено: ", popped);
                    }
                }

                welcome();
            }

            if (cmd == 4)
            {
                printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
                       "Освободившиеся адреса:");
                output_array(*fmem);

                welcome();
            }

            if (cmd == 5)
            {
                uint64_t start, end;

                printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
                       "Результат и время, полученное на стеке на основе массива:");

                start = tick();
                int stack_status = decsubseq_arr(stack);
                end = tick();

                if (!stack_status)
                {
                    printf("%s\n", "Подпоследовательности не найдены.");
                }
                else
                {
                    printf(ANSI_COLOR_MAGENTA "%s%ju\n" ANSI_COLOR_RESET,
                           "Время выполнения: ", end - start);
                }

                printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
                       "Результат и время, полученное на стеке на основе списка:");

                start = tick();
                int list_status = decsubseq_list(&root, fmem);
                end = tick();

                if (!list_status)
                {
                    printf("%s\n", "Подпоследовательности не найдены.");
                }
                else
                {
                    printf(ANSI_COLOR_MAGENTA "%s%ju\n" ANSI_COLOR_RESET,
                           "Время выполнения: ", end - start);
                }

                welcome();
            }
        }
    }

    free_stacka(stack);
    free_stackl(&root, fmem);
    free_array(fmem);

    return OK;
}