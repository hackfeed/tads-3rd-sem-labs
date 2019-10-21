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
    sparse_t sparse_a, sparse_b;
    int dots_a, dots_b, dots_sum = 0;

    input_interval(&matrix_a.rows, 0, 1000);
    input_interval(&matrix_a.columns, 0, 1000);
    input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns);

    create(&matrix_a);
    input(&matrix_a, dots_a);
    output(&matrix_a);

    matrix_b.rows = matrix_a.rows;
    matrix_b.columns = matrix_a.columns;

    input_interval(&dots_b, 0, matrix_a.rows * matrix_a.columns);

    create(&matrix_b);
    input(&matrix_b, dots_b);
    output(&matrix_b);

    screate(&sparse_a, dots_a, matrix_a.columns);
    sinput(&sparse_a, matrix_a);
    soutput(sparse_a);

    screate(&sparse_b, dots_b, matrix_a.columns);
    sinput(&sparse_b, matrix_b);
    soutput(sparse_b);

    sdots(sparse_a, sparse_b, &dots_sum);

    printf("~%d~\n", dots_sum);

    deletee(&matrix_a);
    sdelete(&sparse_a);
    deletee(&matrix_b);
    sdelete(&sparse_b);

    return OK;
}