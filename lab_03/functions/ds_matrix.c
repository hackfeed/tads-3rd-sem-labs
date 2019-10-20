/*
CDIO utilities for matrix data structure.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../headers/defines.h"
#include "../headers/data_structures.h"

#include "../headers/func_io.h"

void fill_matrix(matrix_t *const matrix)
{
    for (int row = 0; row < matrix->rows; ++row)
    {
        for (int col = 0; col < matrix->columns; ++col)
        {
            *(*(matrix->matrix + row) + col) = 0;
        }
    }
}

/*
Dynamic matrix creation.

Input data:
* matrix_t *const matrix - matrix to be created.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int create(matrix_t *const matrix)
{
    matrix->matrix = (type_t **)malloc(matrix->rows * sizeof(type_t *));

    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int row = 0; row < matrix->rows; ++row)
    {
        *(matrix->matrix + row) = (type_t *)malloc(matrix->columns * sizeof(type_t));

        if (!*(matrix->matrix + row))
        {
            for (int clean = 0; clean < row; ++clean)
            {
                free(*(matrix->matrix + clean));
            }

            free(matrix->matrix);

            return MEMORY_ALLOC_ERROR;
        }
    }

    fill_matrix(matrix);

    return OK;
}

/*
Dynamic matrix deletion.

Input data:
* matrix_t *const matrix - mattrix to be deleted.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int deletee(matrix_t *const matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int clean = 0; clean < matrix->rows; ++clean)
    {
        if (*(matrix->matrix + clean))
        {
            free(*(matrix->matrix + clean));
        }
    }

    free(matrix->matrix);

    return OK;
}

/*
Dynamic matrix input.

Input data:
* matrix_t *const matrix - matrix to be inputed.
* const int dots - amount of dots to be entered.

Output data:
* Return code - OK, MEMORY_ALLOC_ERROR or MATRIX_INPUT_ERROR.
*/
int input(matrix_t *const matrix, const int dots)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int dot = 0; dot < dots; ++dot)
    {
        int row, col, cur;

        if (input_interval(&row, 0, matrix->rows - 1))
        {
            return INVALID_INT_INPUT_ERROR;
        }

        if (input_interval(&col, 0, matrix->columns - 1))
        {
            return INVALID_INT_INPUT_ERROR;
        }

        if (input_interval(&cur, -1000, 99999))
        {
            return INVALID_INT_INPUT_ERROR;
        }

        *(*(matrix->matrix + row) + col) = cur;
    }

    return OK;
}

/*
Dynamic matrix output.

Input data:
* const matrix_t *const matrix - matrix to be outputed.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int output(const matrix_t *const matrix)
{
    if (!matrix->matrix)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int row = 0; row < matrix->rows; ++row)
    {
        for (int col = 0; col < matrix->columns; ++col)
        {
            printf(out_spec, *(*(matrix->matrix + row) + col));
        }

        printf("%s", "\n");
    }

    return OK;
}