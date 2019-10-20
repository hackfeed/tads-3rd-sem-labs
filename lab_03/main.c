#include <stdio.h>

#include "headers/func_io.h"
#include "headers/ds_matrix.h"
#include "headers/func_matrix.h"

int main()
{
    welcome();

    matrix_t matrix_a, matrix_b, matrix_res;
    int dots_a, dots_b;

    input_interval(&matrix_a.rows, 0, 1000);
    input_interval(&matrix_a.columns, 0, 1000);

    matrix_b.rows = matrix_a.rows;
    matrix_b.columns = matrix_a.columns;
    matrix_res.rows = matrix_a.rows;
    matrix_res.columns = matrix_a.columns;

    input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns);
    create(&matrix_a);
    input(&matrix_a, dots_a);

    input_interval(&dots_b, 0, matrix_a.rows * matrix_a.columns);
    create(&matrix_b);
    input(&matrix_b, dots_b);

    create(&matrix_res);
    output(&matrix_res);
    classic_sum(matrix_a, matrix_b, &matrix_res);
    output(&matrix_res);

    deletee(&matrix_a);
    deletee(&matrix_b);
    deletee(&matrix_res);

    return OK;
}