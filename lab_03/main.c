#include <stdio.h>

#include "headers/defines.h"
#include "headers/func_io.h"
#include "headers/ds_matrix.h"
#include "headers/ds_sparse.h"
#include "headers/func_matrix.h"

int main()
{
    welcome();

    matrix_t matrix_a;
    sparse_t sparse_a;
    int dots_a;

    input_interval(&matrix_a.rows, 0, 1000);
    input_interval(&matrix_a.columns, 0, 1000);
    input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns);

    create(&matrix_a);
    input(&matrix_a, dots_a);
    output(&matrix_a);
    
    screate(&sparse_a, dots_a, matrix_a.columns);
    sinput(&sparse_a, matrix_a);
    soutput(sparse_a);

    deletee(&matrix_a);
    sdelete(&sparse_a);

    return OK;
}