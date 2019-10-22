#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../headers/defines.h"
#include "../headers/data_structures.h"

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

/*
Classic matrix addition.

Input data:
* const matrix_t matrix_a, const matrix_t matrix_b - matrices to be added.
* matrix_t *const matrix_res - result matrix.
*/
void classic_sum(const matrix_t matrix_a, const matrix_t matrix_b,
                 matrix_t *const matrix_res, uint64_t *const ticks)
{
    uint64_t start = tick();
    for (int row = 0; row < matrix_a.rows; ++row)
    {
        for (int col = 0; col < matrix_a.columns; ++col)
        {
            *(*(matrix_res->matrix + row) + col) =
                *(*(matrix_a.matrix + row) + col) + *(*(matrix_b.matrix + row) + col);
        }
    }
    uint64_t end = tick();

    *ticks = end - start;
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
            for (int j = 0; j < b_column; ++j)
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
    if (a_len == 0 && b_len != 0)
    {
        return B_LESS;
    }

    if (b_len == 0 && a_len != 0)
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

    if (a_min == b_min && a_min == 1000 && b_min == 1000)
    {
        return UB;
    }

    *(a_arr + a_pos) = 1000;
    *(b_arr + b_pos) = 1000;

    return EQUAL;
}

/*
Sparse matrix addition.

Input data:
* const sparse_t sparse_a, const sparse_t sparse_b - matrices to be added.
* sparse_t *const sparse_res - result matrix.
*/
void sparse_sum(const sparse_t sparse_a, const sparse_t sparse_b,
                sparse_t *const sparse_res, uint64_t *const ticks)
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
            for (int j = 0; j < b_column; ++j)
            {
                if (*(a_arr + i) == *(b_arr + j))
                {
                    matches++;
                }
            }
        }

        int range = a_column + b_column - matches;

        uint64_t start = tick();
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

        uint64_t end = tick();
        *ticks += end - start;

        free(a_arr);
        free(b_arr);
    }

    return OK;
}

int fill_col_entry(sparse_t *const sparse, const matrix_t matrix)
{
    int elems = 0;
    for (int col = 0; col < matrix.columns; ++col)
    {
        int col_elems = 0;
        for (int row = 0; row < matrix.rows; ++row)
        {
            if (*(*(matrix.matrix + row) + col) != 0)
            {
                col_elems++;
                elems++;
            }
        }

        *(sparse->col_entry + col) = elems - col_elems;
    }
}

int random(const int offset)
{
    int doom_seed[] = {
        151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30,
        69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94,
        252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 8, 237, 149, 56, 87, 174, 20, 125, 136, 171,
        168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
        60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
        1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159,
        86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147,
        118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183,
        170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129,
        22, 39, 253, 9, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
        251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
        49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
        138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180};

    time_t now = time(0) + offset + doom_seed[offset % 256];
    int seed = now % 256;

    return abs(doom_seed[seed] + doom_seed[(seed + 1) % 256] - doom_seed[(seed + 2) % 256]);
}

/*
Get amount of empty tiles in matrix.

Input data:
* const matrix_t matrix - matrix to be checeked.

Output data:
* Amount of empty tiles.
*/
int get_empty_tiles(const matrix_t matrix)
{
    int empty_tiles = 0;

    for (int row = 0; row < matrix.rows; ++row)
    {
        for (int col = 0; col < matrix.columns; ++col)
        {
            if (*(*(matrix.matrix + row) + col) == 0)
            {
                empty_tiles++;
            }
        }
    }

    return empty_tiles;
}

/*
Fill matrix matrix with 4 (10% chance) or 2 (90% chance).

Input data:
* matrix_t *const matrix - matrix to be filled.
*/
void gorandom(matrix_t *const matrix, int percent)
{
    int empty_tiles = get_empty_tiles(*matrix);

    int rand = random(empty_tiles) % empty_tiles;
    int tile = random(empty_tiles);

    for (int row = 0; row < matrix->rows; ++row)
    {
        for (int col = 0; col < matrix->columns; ++col)
        {
            if (!(*(*(matrix->matrix + row) + col)) && rand)
            {
                --rand;
            }
            else
            {
                if (!(*(*(matrix->matrix + row) + col)) && !rand)
                {
                    *(*(matrix->matrix + row) + col) = tile;

                    return;
                }
            }
        }
    }
}