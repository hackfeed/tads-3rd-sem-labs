#include "include/queueops.h"

int main()
{
    int capacity = 5, max_capacity;
    arr_t *fmem = NULL;
    queuelist_t *queuelist = NULL;
    queuearr_t *queuearr = NULL;

    queuelist = create_queuelist(10000);
    queuearr = create_queuearr(10000);
    fmem = create_array(30000);

    list_model(queuelist, fmem, 0, 6, 0, 1, 5);
    array_model(queuearr, 0, 6, 0, 1, 5);
    // freequeuearr(queuelist);
    // free_array(fmem);

    return EOK;

    // int cmd = -1;

    // welcome();

    // while (cmd)
    // {
    //     if (input_interval(&cmd, 0, 11))
    //     {
    //         printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                "Введена недопустимая команда! Повторите попытку.");

    //         welcome();
    //     }

    //     else
    //     {
    //         if (cmd == 1)
    //         {
    //             if (stack)
    //             {
    //                 printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                        "Стек уже существует! Выход из программы..");

    //                 free_stacka(stack);
    //                 free_stackl(&root, fmem);
    //                 free_array(fmem);

    //                 return OK;
    //             }
    //             else
    //             {
    //                 printf("%s\n", "Введите максимальное число элементов в стеке:");
    //                 if (input_interval(&max_capacity, 0, INT8_MAX))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     return OK;
    //                 }

    //                 printf("%s\n", "Введите начальное число элементов в стеке:");
    //                 if (input_interval(&capacity, 0, max_capacity))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     return OK;
    //                 }

    //                 stack = create_stacka(max_capacity);

    //                 printf("%s\n", "Введите элементы стека (целые числа):");
    //                 if (input_stacka(capacity, stack))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     free_stacka(stack);
    //                     free_stackl(&root, fmem);
    //                     free_array(fmem);

    //                     return OK;
    //                 }

    //                 printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                        "Стек успешно заполнен.");
    //             }

    //             welcome();
    //         }

    //         if (cmd == 2)
    //         {
    //             printf("%s\n", "Введите элемент для добавления в стек:");
    //             if (is_fulla(stack))
    //             {
    //                 printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                        "Размер стека достиг максимального значения!");
    //             }
    //             else
    //             {
    //                 if (input_stacka(1, stack))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     free_stacka(stack);

    //                     return OK;
    //                 }

    //                 printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                        "Значение успешно помещено в стек.");
    //             }

    //             welcome();
    //         }

    //         if (cmd == 3)
    //         {
    //             if (is_emptya(stack))
    //             {
    //                 printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET,
    //                        "Стек пуст!");
    //             }
    //             else
    //             {
    //                 int popped = popa(stack);
    //                 printf(ANSI_COLOR_GREEN "%s%d\n" ANSI_COLOR_RESET,
    //                         "Значение успешно извлечено: ", popped);
    //             }

    //             welcome();
    //         }

    //         if (cmd == 4)
    //         {
    //             uint64_t start, end;

    //             printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                    "Результат и время, полученное на стеке на основе массива:");

    //             start = tick();
    //             int stack_status = decsubseq_arr(stack);
    //             end = tick();

    //             if (!stack_status)
    //             {
    //                 printf("%s\n", "Подпоследовательности не найдены.");
    //             }
    //             else
    //             {
    //                 printf(ANSI_COLOR_MAGENTA "%s%ju\n" ANSI_COLOR_RESET,
    //                        "Время выполнения: ", end - start);
    //             }

    //             welcome();
    //         }

    //         if (cmd == 5)
    //         {
    //             printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                    "Текущее состояние стека:");
    //             output_stacka(stack);

    //             welcome();
    //         }

    //         if (cmd == 6)
    //         {
    //             if (root)
    //             {
    //                 printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                        "Стек уже существует! Выход из программы..");

    //                 free_stacka(stack);
    //                 free_stackl(&root, fmem);
    //                 free_array(fmem);

    //                 return OK;
    //             }
    //             else
    //             {
    //                 printf("%s\n", "Введите максимальное число элементов в стеке:");
    //                 if (input_interval(&max_capacity, 0, INT8_MAX))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     return OK;
    //                 }

    //                 fmem = create_array(max_capacity * max_capacity);

    //                 printf("%s\n", "Введите начальное число элементов в стеке:");
    //                 if (input_interval(&capacity, 0, max_capacity))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     return OK;
    //                 }

    //                 printf("%s\n", "Введите элементы стека (целые числа):");
    //                 if (input_stackl(capacity, &root, max_capacity))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     free_stacka(stack);
    //                     free_stackl(&root, fmem);
    //                     free_array(fmem);

    //                     return OK;
    //                 }

    //                 printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                        "Стек успешно заполнен.");
    //             }

    //             welcome();
    //         }

    //         if (cmd == 7)
    //         {
    //             printf("%s\n", "Введите элемент для добавления в стек:");
    //             if (is_fulll(root, max_capacity))
    //             {
    //                 printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                        "Размер стека достиг максимального значения!");
    //             }
    //             else
    //             {
    //                 if (input_stackl(1, &root, max_capacity))
    //                 {
    //                     printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
    //                            "Введено недопустимое значение! Повторите попытку.");

    //                     free_stackl(&root, fmem);

    //                     return OK;
    //                 }

    //                 check_top(root, fmem);

    //                 printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                        "Значение успешно помещено в стек.");
    //             }

    //             welcome();
    //         }

    //         if (cmd == 8)
    //         {
    //             if (is_emptyl(root))
    //             {
    //                 printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET,
    //                        "Стек пуст!");
    //             }
    //             else
    //             {
    //                 int popped = popl(&root, fmem);
    //                 printf(ANSI_COLOR_GREEN "%s%d\n" ANSI_COLOR_RESET,
    //                         "Значение успешно извлечено: ", popped);
    //             }

    //             welcome();
    //         }

    //         if (cmd == 9)
    //         {
    //             printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                    "Массив освободившихся адресов:");
    //             output_array(*fmem);

    //             welcome();
    //         }

    //         if (cmd == 10)
    //         {
    //             uint64_t start, end;

    //             printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                    "Результат и время, полученное на стеке на основе списка:");

    //             start = tick();
    //             int stack_status = decsubseq_list(&root, fmem);
    //             end = tick();

    //             if (!stack_status)
    //             {
    //                 printf("%s\n", "Подпоследовательности не найдены.");
    //             }
    //             else
    //             {
    //                 printf(ANSI_COLOR_MAGENTA "%s%ju\n" ANSI_COLOR_RESET,
    //                        "Время выполнения: ", end - start);
    //             }

    //             welcome();
    //         }

    //         if (cmd == 11)
    //         {
    //             printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,
    //                    "Текущее состояние стека:");
    //             output_stackl(root);

    //             welcome();
    //         }
    //     }
    // }

    // free_stacka(stack);
    // free_stackl(&root, fmem);
    // free_array(fmem);

    // return OK;
}