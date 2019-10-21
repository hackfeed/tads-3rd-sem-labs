#include <inttypes.h>

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
        for (int rp = *(sparse_a.col_entry + col);
             rp < sparse_a.cols_amount - *(sparse_a.col_entry + col) - 1;
             ++rp)
        {
            if (*(sparse_a.row_entry + rp) != *(sparse_b.row_entry + rp))
            {
                (*dots)++;
            }
        }
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
