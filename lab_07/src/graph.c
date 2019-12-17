#include "include/graph.h"

chain_t *chcreate(adjmat_t matrix)
{
    int edges = 0;

    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            if (matrix.matrix[i][j])
            {
                edges++;
            }
        }
    }

    edges /= 2;

    chain_t *chain = (chain_t *)malloc(sizeof(chain_t));
    if (!chain)
    {
        return NULL;
    }
    chain->size = edges;
    chain->edges = (edge_t *)malloc(sizeof(edge_t) * edges);
    if (!chain->edges)
    {
        free(chain);
        return NULL;
    }

    edge_t edge;
    int idx = 0;

    adjmat_t *copy = amcopy(matrix);

    for (int i = 0; i < copy->size; ++i)
    {
        for (int j = 0; j < copy->size; ++j)
        {
            if (copy->matrix[i][j])
            {
                edge.fvertex = i;
                edge.svertex = j;
                chain->edges[idx] = edge;

                copy->matrix[i][j] = 0;
                copy->matrix[j][i] = 0;

                idx++;
            }
        }
    }

    return chain;
}

edge_t **alrows(const int n, const int m)
{
    edge_t **data = (edge_t **)malloc(sizeof(edge_t *) * n);
    if (!data)
    {
        return NULL;
    }

    for (int i = 0; i < n; ++i)
    {
        data[i] = (edge_t *)malloc(sizeof(edge_t) * m);
        if (!data[i])
        {
            for (int j = 0; j < i; ++j)
            {
                free(data[j]);
                return NULL;
            }
        }
    }

    return data;
}