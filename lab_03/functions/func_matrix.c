#include <inttypes.h>
#include <stdlib.h>

#include "../headers/defines.h"
#include "../headers/data_structures.h"

/*
Classic matrix addition.

Input data:
* const matrix_t matrix_a, const matrix_t matrix_b - matrices to be added.
* matrix_t *const matrix_res - result matrix.
*/
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

/*
Count non-zero dots after sparse addition.

Input data:
* const sparse_t sparse_a, const sparse_t sparse_b - sparse matrices to be 
checked.
* int *const dots - overall dots.
*/
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

/*
Find minimum of two arrays.

Input data:
* type_t *a_arr, const int a_len, type_t *b_arr, const int b_len - arrays and 
their properties.

Output data:
* Return sign: A_LESS (if a_arr less than b_arr), B_LESS (if b_arr less than 
a_arr) or EQUAL (otherwise).
*/
int arrays_min(type_t *a_arr, const int a_len, type_t *b_arr, const int b_len)
{
    if (a_len == 0)
    {
        return B_LESS;
    }

    if (b_len == 0)
    {
        return A_LESS;
    }

    int a_min = *a_arr, b_min = *b_arr;
    int a_pos = 0, b_pos = 0;

    for (int a = 0; a < a_len; ++a)
    {
        if (*(a_arr + a) < a_min)
        {
            a_min = *(a_arr + a);
            a_pos = a;
        }
    }

    for (int b = 0; b < b_len; ++b)
    {
        if (*(b_arr + b) < b_min)
        {
            b_min = *(b_arr + b);
            b_pos = b;
        }
    }

    if (a_min < b_min)
    {
        *(a_arr + a_pos) = 1000;

        return A_LESS;
    }

    if (b_min < a_min)
    {
        *(b_arr + b_pos) = 1000;

        return B_LESS;
    }

    if (*(a_arr + a_pos) < *(b_arr + b_pos))
    {
        *(a_arr + a_pos) = 1000;
    }
    else
    {
        *(b_arr + b_pos) = 1000;
    }

    return EQUAL;
}

/*
Sparse matrix addition.

Input data:
* const sparse_t sparse_a, const sparse_t sparse_b - matrices to be added.
* sparse_t *const sparse_res - result matrix.
*/
void sparse_sum(const sparse_t sparse_a, const sparse_t sparse_b,
                sparse_t *const sparse_res)
{
    int cur_el = 0;
    int a_glob = 0;
    int b_glob = 0;

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

        int range = a_column + b_column - matches;

        for (int i = 0; i < range; ++i)
        {
            int where = arrays_min(a_arr, a_column, b_arr, b_column);

            if (where == A_LESS)
            {
                *(sparse_res->elems + cur_el) = *(sparse_a.elems + a_glob);
                *(sparse_res->row_entry + cur_el) = *(sparse_a.row_entry + a_glob);
                cur_el++;
                a_glob++;
            }

            if (where == B_LESS)
            {
                *(sparse_res->elems + cur_el) = *(sparse_b.elems + b_glob);
                *(sparse_res->row_entry + cur_el) = *(sparse_b.row_entry + b_glob);
                cur_el++;
                b_glob++;
            }

            if (where == EQUAL)
            {
                *(sparse_res->elems + cur_el) = *(sparse_a.elems + a_glob) + *(sparse_b.elems + b_glob);
                *(sparse_res->row_entry + cur_el) = *(sparse_a.row_entry + a_glob);
                cur_el++;
                a_glob++;
                b_glob++;
            }
        }

        *(sparse_res->col_entry + col) = cur_el - range;

        free(a_arr);
        free(b_arr);
    }

    return OK;
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
