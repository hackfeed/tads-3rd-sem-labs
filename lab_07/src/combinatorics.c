#include "include/combinatorics.h"

unsigned long fact(const int num)
{
    unsigned long res = 1;

    for (int i = 1; i <= num; ++i)
    {
        res *= i;
    }

    return res;
}

int combs(const int n, const int k)
{
    return (fact(n) / (fact(k) * fact(n - k)));
}

void mkcombs(edge_t **ans, edge_t *tmp, chain_t chain, const int tmp_size, const int n,
             const int left, const int k, int *const idx, int *crow)
{
    if (k == 0)
    {
        for (int i = 0; i < tmp_size; ++i)
        {
            ans[*crow][i] = tmp[i];
        }
        (*crow)++;
        return;
    }

    for (int i = left; i <= n; ++i)
    {
        tmp[(*idx)++] = chain.edges[i - 1];
        mkcombs(ans, tmp, chain, tmp_size, n, i + 1, k - 1, idx, crow);
        (*idx)--;
    }
}

edge_t **mkcombsvect(chain_t chain, const int rows, const int n,
                     const int k, int *const idx, int *crow)
{
    edge_t **ans = alrows(rows, k);
    edge_t *tmp = (edge_t *)malloc(sizeof(edge_t) * k);

    mkcombs(ans, tmp, chain, k, n, 1, k, idx, crow);
    free(tmp);

    return ans;
}

int is_conn(adjmat_t matrix)
{
    int *visited = (int *)calloc(matrix.size, sizeof(int));
    dfs(matrix, 0, visited);

    for (int i = 0; i < matrix.size; ++i)
    {
        if (visited[i] == 0)
        {
            free(visited);
            return FALSE;
        }
    }
    free(visited);

    return TRUE;
}

adjmat_t *ckcut(adjmat_t matrix, edge_t **vars, const int cmbs, const int len)
{
    adjmat_t *copy = amcopy(matrix);
    adjmat_t *stable = copy;

    for (int i = 0; i < cmbs; ++i)
    {
        if (!is_conn(*copy))
        {
            return copy;
        }
        copy = stable;
        for (int j = 0; j < len; ++j)
        {
            copy->matrix[vars[i][j].fvertex][vars[i][j].svertex] = 0;
            copy->matrix[vars[i][j].svertex][vars[i][j].fvertex] = 0;
        }
    }
    amfree(copy);

    return NULL;
}

adjmat_t *cutgraph(adjmat_t matrix)
{
    adjmat_t *result;

    chain_t *chain = chcreate(matrix);
    for (int i = 1; i <= chain->size; ++i)
    {
        int idx = 0, crow = 0;
        int cmbs = combs(chain->size, i);
        edge_t **vars = mkcombsvect(*chain, cmbs, chain->size, i, &idx, &crow);

        result = ckcut(matrix, vars, cmbs, i);

        if (result)
        {
            chfree(chain);
            frrows(vars, cmbs);
            return result;
        }
        frrows(vars, cmbs);
    }
    chfree(chain);
    amfree(result);

    return NULL;
}