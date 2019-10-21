#include <inttypes.h>
#include <stdlib.h>

#include "../headers/defines.h"
#include "../headers/data_structures.h"

void classic_sum(const matrix_t matrix_a, const matrix_t matrix_b,
                 matrix_t *const matrix_res)
{
    for (int row = 0; row < matrix_a.rows; ++row)
    {
        for (int col = 0; col < matrix_a.columns; ++col)
        {
            *(*(matrix_res->matrix + row) + col) =
                *(*(matrix_a.matrix + row) + col) + *(*(matrix_b.matrix + row) + col);
        }
    }
}

int sdots(const sparse_t sparse_a, const sparse_t sparse_b, int *const dots)
{
    for (int col = 0; col < sparse_a.cols_amount; ++col)
    {
        type_t *a_arr, *b_arr;
        int a_ind = 0, b_ind = 0;
        int cur_a, cur_b;

        if (col + 1 != sparse_a.cols_amount)
        {
            cur_a = *(sparse_a.col_entry + col + 1);
            cur_b = *(sparse_b.col_entry + col + 1);
        }
        else
        {
            cur_a = sparse_a.elems_amount;
            cur_b = sparse_b.elems_amount;
        }

        int a_column = cur_a - *(sparse_a.col_entry + col);
        int b_column = cur_b - *(sparse_b.col_entry + col);
        a_arr = (type_t *)calloc(a_column, sizeof(type_t));
        b_arr = (type_t *)calloc(b_column, sizeof(type_t));

        for (int a_col = *(sparse_a.col_entry + col); a_col < cur_a; ++a_col)
        {
            if (a_arr)
            {
                *(a_arr + a_ind) = *(sparse_a.row_entry + a_col);
            }
            a_ind++;
        }

        for (int b_col = *(sparse_b.col_entry + col); b_col < cur_b; ++b_col)
        {
            if (b_arr)
            {
                *(b_arr + b_ind) = *(sparse_b.row_entry + b_col);
            }
            b_ind++;
        }

        int matches = 0;
        for (int i = 0; i < a_column; ++i)
        {
            for (int j = i; j < b_column; ++j)
            {
                if (*(a_arr + i) == *(b_arr + j))
                {
                    matches++;
                }
            }
        }

        free(a_arr);
        free(b_arr);

        *dots += a_column + b_column - matches;
    }

    return OK;
}

void sparse_sum(const sparse_t sparse_a, const sparse_t sparse_b,
                sparse_t *const sparse_res)
{
}

/*
Processor's tick counter.

Output data:
* ticks - processor's ticks until return statement.
*/
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}
