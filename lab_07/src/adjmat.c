#include "include/adjmat.h"

adjmat_t *amcreate(const int size)
{
    adjmat_t *matrix = (adjmat_t *)malloc(sizeof(adjmat_t));
    if (!matrix)
    {
        return NULL;
    }
    matrix->size = size;
    matrix->matrix = (int **)malloc(sizeof(int *) * size);
    if (!matrix->matrix)
    {
        free(matrix);
        return NULL;
    }
    for (int i = 0; i < size; ++i)
    {
        matrix->matrix[i] = (int *)calloc(size, sizeof(int));
        if (!matrix->matrix[i])
        {
            for (int j = 0; j < i; ++j)
            {
                free(matrix->matrix[j]);
            }
            free(matrix->matrix);
            free(matrix);

            return NULL;
        }
    }

    return matrix;
}

void amfree(adjmat_t *matrix)
{
    for (int i = 0; i < matrix->size; ++i)
    {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}

adjmat_t *amcopy(adjmat_t matrix)
{
    adjmat_t *copy = amcreate(matrix.size);

    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            if (matrix.matrix[i][j])
            {
                copy->matrix[i][j] = GOT_CONNECTION;
            }
        }
    }

    return copy;
}

int amfill(FILE *const stream, adjmat_t *const matrix)
{
    int fvertex, svertex;
    int ec;

    while (TRUE)
    {
        ec = rnginput(&fvertex, -1, matrix->size - 1);
        if (ec)
        {
            return ec;
        }
        if (fvertex == EOI)
        {
            break;
        }
        ec = rnginput(&svertex, 0, matrix->size - 1);
        if (ec)
        {
            return ec;
        }

        if (fvertex == svertex)
        {
            return EINVALIDVERTEXPAIR;
        }

        matrix->matrix[fvertex][svertex] = GOT_CONNECTION;
        matrix->matrix[svertex][fvertex] = GOT_CONNECTION;
    }

    return EOK;
}

void amouptut(FILE *const stream, const adjmat_t matrix)
{
    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            fprintf(stream, "%d ", matrix.matrix[i][j]);
        }
        fprintf(stream, "\n");
    }
}

void dfs(const adjmat_t matrix, const int vertex, int *visited)
{
    visited[vertex] = TRUE;

    for (int i = 0; i < matrix.size; ++i)
    {
        if (matrix.matrix[vertex][i] && !visited[i])
        {
            dfs(matrix, i, visited);
        }
    }
}