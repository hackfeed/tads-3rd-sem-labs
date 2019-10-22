/*
CDIO utilities for sparse matrix data structure.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../headers/defines.h"
#include "../headers/data_structures.h"

#include "../headers/func_io.h"

/*
Fill col_entry array with -1 value.

Input data:
* sparse_t *const sparse - sparse matrix to be changed.
*/
void fill_sparse(sparse_t *const sparse)
{
    for (int ent = 0; ent < sparse->elems_amount; ++ent)
    {
        *(sparse->elems + ent) = 0;
    }
    for (int ent = 0; ent < sparse->elems_amount; ++ent)
    {
        *(sparse->row_entry + ent) = 0;
    }
    for (int ent = 0; ent < sparse->cols_amount; ++ent)
    {
        *(sparse->col_entry + ent) = -1;
    }
}

/*
Sparse matrix creation.

Input data:
* sparse_t *const sparse - sparse matrix to be created.
* const int dots - amount non-zero values in matrix.
* const int cols - amount of base matrix columns.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int screate(sparse_t *const sparse, const int dots, const int cols)
{
    sparse->elems = (type_t *)malloc(dots * sizeof(type_t));
    sparse->row_entry = (int *)malloc(dots * sizeof(int));
    sparse->col_entry = (int *)malloc(cols * sizeof(int));
    sparse->elems_amount = dots;
    sparse->cols_amount = cols;

    if (!sparse->elems || !sparse->row_entry || !sparse->col_entry)
    {
        return MEMORY_ALLOC_ERROR;
    }

    fill_sparse(sparse);

    return OK;
}

/*
Sparse matrix deletion.

Input data:
* sparse_t *const sparse - matrix to be deleted.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int sdelete(sparse_t *const sparse)
{
    if (!sparse->elems || !sparse->row_entry || !sparse->col_entry)
    {
        return MEMORY_ALLOC_ERROR;
    }

    free(sparse->elems);
    free(sparse->row_entry);
    free(sparse->col_entry);

    return OK;
}

/*
Sparse matrix input.

Input data:
* sparse_t *const sparse - sparse matrix to be inputted.
* matrix_t *const matrix - base matrix.

Output data:
* Return code - OK, MEMORY_ALLOC_ERROR or MATRIX_INPUT_ERROR.
*/
int sinput(sparse_t *const sparse, const matrix_t matrix)
{
    if (!matrix.matrix || !sparse->elems || !sparse->row_entry || !sparse->col_entry)
    {
        return MEMORY_ALLOC_ERROR;
    }

    int ind = -1;
    int cur = 0;

    for (int col = 0; col < matrix.columns; ++col)
    {
        for (int row = 0; row < matrix.rows; ++row)
        {
            if (*(*(matrix.matrix + row) + col) != 0)
            {
                ind++;
                if (*(sparse->col_entry + col) == -1)
                {
                    *(sparse->col_entry + col) = ind;
                }
            }
        }
    }

    for (int col = 0; col < matrix.columns; ++col)
    {
        for (int row = 0; row < matrix.rows; ++row)
        {
            if (*(*(matrix.matrix + row) + col) != 0)
            {
                *(sparse->elems + cur) = *(*(matrix.matrix + row) + col);
                *(sparse->row_entry + cur) = row;
                cur++;
            }
        }
    }

    for (int ent = 0; ent < sparse->cols_amount; ++ent)
    {
        if (*(sparse->col_entry + ent) == -1)
        {
            for (int search = ent; search < sparse->cols_amount; ++search)
            {
                if (*(sparse->col_entry + search) != -1)
                {
                    *(sparse->col_entry + ent) = *(sparse->col_entry + search);
                    break;
                }

                *(sparse->col_entry + search) = sparse->elems_amount;
            }
        }
    }

    return OK;
}

/*
Sparse matrix output.

Input data:
* const sparse_t sparse - sparse matrix to be outputed.

Output data:
* Return code - OK or MEMORY_ALLOC_ERROR.
*/
int soutput(const sparse_t sparse)
{
    if (!sparse.elems || !sparse.row_entry || !sparse.col_entry)
    {
        return MEMORY_ALLOC_ERROR;
    }

    for (int el = 0; el < sparse.elems_amount; ++el)
    {
        printf(out_spec, *(sparse.elems + el));
    }
    printf("%s", "\n");

    for (int el = 0; el < sparse.elems_amount; ++el)
    {
        printf("%5d ", *(sparse.row_entry + el));
    }
    printf("%s", "\n");

    for (int el = 0; el < sparse.cols_amount; ++el)
    {
        printf("%5d ", *(sparse.col_entry + el));
    }
    printf("%s", "\n");

    return OK;
}