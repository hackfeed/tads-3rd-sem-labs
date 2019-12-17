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

void chfree(chain_t *chain)
{
    free(chain->edges);
    free(chain);
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

void frrows(edge_t **data, const int n)
{
    for (int i = 0; i < n; ++i)
    {
        free(data[i]);
    }
}

void gvexport(adjmat_t matrix, adjmat_t result)
{
    FILE *export = fopen("graph.txt", "w");
    fprintf(export, "graph {\n");

    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            if (matrix.matrix[i][j])
            {
                matrix.matrix[j][i] = 0;
            }
        }
    }

    for (int i = 0; i < result.size; ++i)
    {
        for (int j = 0; j < result.size; ++j)
        {
            if (result.matrix[i][j])
            {
                result.matrix[j][i] = 0;
            }
        }
    }

    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            if (matrix.matrix[i][j] && result.matrix[i][j])
            {
                fprintf(export, "%d -- %d;\n", i, j);
            }
            if (matrix.matrix[i][j] && !result.matrix[i][j])
            {
                fprintf(export, "%d -- %d[color=red,penwidth=3.0];\n", i, j);
            }
        }
        fprintf(export, "%d;\n", i);
    }

    fprintf(export, "}\n");
    fclose(export);

    system("dot -Tpng graph.txt -o graph.png");
    system("gwenview graph.png");
}