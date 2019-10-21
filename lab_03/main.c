#include <stdio.h>

#include "headers/defines.h"
#include "headers/func_io.h"
#include "headers/ds_matrix.h"
#include "headers/ds_sparse.h"
#include "headers/func_matrix.h"

int main()
{
    welcome();

    matrix_t matrix_a, matrix_b;
    sparse_t sparse_a, sparse_b, sparse_res;
    int dots_a, dots_b, dots_sum = 0;

    input_interval(&matrix_a.rows, 0, 1000);
    input_interval(&matrix_a.columns, 0, 1000);
    input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns);

    create(&matrix_a);
    input(&matrix_a, dots_a);

    matrix_b.rows = matrix_a.rows;
    matrix_b.columns = matrix_a.columns;

    input_interval(&dots_b, 0, matrix_a.rows * matrix_a.columns);

    create(&matrix_b);
    input(&matrix_b, dots_b);

    screate(&sparse_a, dots_a, matrix_a.columns);
    sinput(&sparse_a, matrix_a);

    screate(&sparse_b, dots_b, matrix_a.columns);
    sinput(&sparse_b, matrix_b);

    sdots(sparse_a, sparse_b, &dots_sum);
    screate(&sparse_res, dots_sum, matrix_a.columns);
    sparse_sum(sparse_a, sparse_b, &sparse_res);
    soutput(sparse_res);

    deletee(&matrix_a);
    sdelete(&sparse_a);
    deletee(&matrix_b);
    sdelete(&sparse_b);
    sdelete(&sparse_res);

    return OK;
}