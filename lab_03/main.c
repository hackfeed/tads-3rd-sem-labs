#include <stdio.h>

#include "headers/func_io.h"

int main()
{
    welcome();

    matrix_t matrix;
    int dots;

    input_interval(&matrix.rows, 0, 1000);
    input_interval(&matrix.columns, 0, 1000);
    input_interval(&dots, 0, matrix.rows * matrix.columns);

    create(&matrix);
    input(&matrix, dots);
    output(&matrix);
    deletee(&matrix);

    return OK;
}