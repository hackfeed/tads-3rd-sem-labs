#include <stdio.h>
#include "../headers/defines.h"
#include "../headers/data_structures.h"
#include "../headers/io.h"

/*
Welcomming print with input rules.
*/
void welcome_print()
{
       printf("%s",
              ANSI_COLOR_GREEN
              "ВЫЧИСЛЕНИЕ ЧАСТНОГО ЦЕЛОГО И ВЕЩЕСТВЕННОГО ЧИСЕЛ\n\n" ANSI_COLOR_RESET
              "Правила ввода:\n" ANSI_COLOR_YELLOW
              "1. Знак перед числом ОБЯЗАТЕЛЕН к вводу ('+' или '-').\n"
              "2. Знак экспоненты ОБЯЗАТЕЛЕН к вводу (латинская 'E' или 'e').\n"
              "3. Знак перед порядком ОБЯЗАТЕЛЕН к вводу ('+' или '-').\n"
              "4. Ведущие нули допустимы.\n"
              "5. Вещественная точка может записываться ТОЛЬКО в виде точки "
              "(запятая ',' недопустима).\n"
              "6. При вводе целого числа максимальная длина составляет 31 символ "
              "(1 символ на знак числа и 30 символов на число).\n"
              "7. При вводе вещественного числа максимальная длина составляет "
              "39 символов (1 символ на знак числа, 1 символ на точку (опционально), "
              "30 символов на мантиссу, 1 символ на знак экспоненты (опционально), "
              "1 символ на знак порядка, 5 символов на порядок.\n\n" ANSI_COLOR_RESET);
}

/*
Input of integer number.

Input data:
* long_t *const entered_num - num to be entered.
*/
void int_input(long_t *const entered_num)
{
       printf("%s",
              ANSI_COLOR_GREEN
              "                            ±|        целая часть         |\n"
              "                            -|--------|---------|---------|\n"
              "                             1       10        20        30\n" ANSI_COLOR_RESET
              "Введите целое число:        ");
       scanf("%s", entered_num);
}

/*
Input of float number.

Input data:
* long_t *const entered_num - num to be entered.
*/
void float_input(long_t *const entered_num)
{
       printf("%s",
              ANSI_COLOR_GREEN
              "                            ±|          мантисса           |E±|pwr|\n"
              "                            -|--------|---------|----------|--|---|\n"
              "                             1       10        20        31  1   5\n" ANSI_COLOR_RESET
              "Введите вещественное число: ");
       scanf("%s", entered_num);
}

/*
Output parsed part of num_t number.

Input data:
* const num_t structed_num - num to be outputed.
*/
void debug_print(const num_t structed_num)
{
       printf(ANSI_COLOR_YELLOW "\n***DEBUG BEGIN***\n" ANSI_COLOR_RESET);
       printf("Parsed sign: %c\n",
              structed_num.num_sign);
       printf("Parsed mantissa: %s\n",
              structed_num.mantissa_part);
       printf("Parsed order: %s\n",
              structed_num.order_part);
       printf("Parsed dot position (-2 if absent): %d\n",
              structed_num.dot_position);
       printf("Parsed exponent position (-1 if absent): %d\n",
              structed_num.exp_position);
       printf("Represented order in int: %d\n",
              structed_num.order_int);
       printf(ANSI_COLOR_YELLOW "***DEBUG END***\n\n" ANSI_COLOR_RESET);
}

/*
Output normalized result num.

Input data:
* const num_t result_num - num to be outputed.
*/
void result_print(const num_t result_num)
{
       printf(ANSI_COLOR_GREEN "Результат вычисления:       " ANSI_COLOR_RESET
                               "%c0.%sE%+d\n",
              result_num.num_sign,
              &result_num.mantissa_part[1], result_num.order_int);
}