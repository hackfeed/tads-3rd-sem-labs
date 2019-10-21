#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "headers/defines.h"
#include "headers/func_io.h"
#include "headers/ds_matrix.h"
#include "headers/ds_sparse.h"
#include "headers/func_matrix.h"

int main()
{
    system("clear");
    welcome();

    matrix_t matrix_a, matrix_b, matrix_res;
    sparse_t sparse_a, sparse_b, sparse_res;
    int dots_a, dots_b, dots_sum = 0;

    int cur_command = -1;

    while (cur_command != 0)
    {
        if (input_interval(&cur_command, 0, 6))
        {
            printf(ANSI_COLOR_RED
                   "%s\n" ANSI_COLOR_RESET,
                   "Введена недопустимая команда! Повторите попытку.");

            welcome();
        }

        else
        {
            if (cur_command == 1)
            {
                printf("%s\n", "Введите количество строк матрицы А (от 1 до 1000):");
                if (input_interval(&matrix_a.rows, 1, 1000))
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Введено недопустимое значение! Повторите попытку.");

                    welcome();
                }

                printf("%s\n", "Введите количество столбцов матрицы А (от 1 до 1000):");
                if (input_interval(&matrix_a.columns, 1, 1000))
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Введено недопустимое значение! Повторите попытку.");

                    welcome();
                }

                printf("%s\n", "Введите количество ненулевых элементов матрицы А (от 1 до 1000):");
                if (input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns))
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Введено недопустимое значение! Повторите попытку.");

                    welcome();
                }

                printf("%s\n", "Введите элементы матрицы А в формате 'строка столбец значение':");
                create(&matrix_a);
                if (input(&matrix_a, dots_a))
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Введено недопустимое значение! Повторите попытку.");

                    welcome();
                }

                matrix_b.rows = matrix_a.rows;
                matrix_b.columns = matrix_a.columns;

                printf("%s\n", "Введите количество ненулевых элементов матрицы В (от 1 до 1000):");
                if (input_interval(&dots_b, 0, matrix_b.rows * matrix_b.columns))
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Введено недопустимое значение! Повторите попытку.");

                    welcome();
                }

                printf("%s\n", "Введите элементы матрицы В в формате 'строка столбец значение':");
                create(&matrix_b);
                if (input(&matrix_b, dots_b))
                {
                    printf(ANSI_COLOR_RED
                           "%s\n" ANSI_COLOR_RESET,
                           "Введено недопустимое значение! Повторите попытку.");

                    welcome();
                }

                matrix_res.rows = matrix_a.rows;
                matrix_res.columns = matrix_a.columns;

                create(&matrix_res);

                screate(&sparse_a, dots_a, matrix_a.columns);
                sinput(&sparse_a, matrix_a);

                screate(&sparse_b, dots_b, matrix_a.columns);
                sinput(&sparse_b, matrix_b);

                sdots(sparse_a, sparse_b, &dots_sum);
                screate(&sparse_res, dots_sum, matrix_a.columns);

                welcome();
            }

            if (cur_command == 2)
            {

                welcome();
            }

            if (cur_command == 3)
            {
                uint64_t start = tick();
                classic_sum(matrix_a, matrix_b, &matrix_res);
                uint64_t end = tick();

                printf(ANSI_COLOR_GREEN
                       "%s%ju\n" ANSI_COLOR_RESET,
                       "Время сложения матриц, хранимых стандартным методом = ",
                       end - start);

                welcome();
            }

            if (cur_command == 4)
            {
                uint64_t start = tick();
                sparse_sum(sparse_a, sparse_b, &sparse_res);
                uint64_t end = tick();

                printf(ANSI_COLOR_GREEN
                       "%s%ju\n" ANSI_COLOR_RESET,
                       "Время сложения матриц, хранимых разреженным "
                       "столбцовым методом = ",
                       end - start);

                welcome();
            }

            if (cur_command == 5)
            {
                printf(ANSI_COLOR_GREEN
                       "%s\n" ANSI_COLOR_RESET,
                       "Матрица А:");
                output(&matrix_a);

                printf(ANSI_COLOR_GREEN
                       "%s\n" ANSI_COLOR_RESET,
                       "Матрица В:");
                output(&matrix_b);

                printf(ANSI_COLOR_GREEN
                       "%s\n" ANSI_COLOR_RESET,
                       "Матрица RES:");
                output(&matrix_res);

                welcome();
            }

            if (cur_command == 6)
            {
                printf(ANSI_COLOR_GREEN
                       "%s\n" ANSI_COLOR_RESET,
                       "Матрица А:");
                soutput(sparse_a);

                printf(ANSI_COLOR_GREEN
                       "%s\n" ANSI_COLOR_RESET,
                       "Матрица В:");
                soutput(sparse_b);

                printf(ANSI_COLOR_GREEN
                       "%s\n" ANSI_COLOR_RESET,
                       "Матрица RES:");
                soutput(sparse_res);

                welcome();
            }
        }
    }

    deletee(&matrix_a);
    sdelete(&sparse_a);
    deletee(&matrix_b);
    sdelete(&sparse_b);
    deletee(&matrix_res);
    sdelete(&sparse_res);

    return OK;
}