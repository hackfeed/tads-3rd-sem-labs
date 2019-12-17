#include "include/combinatorics.h"

int main()
{
    int ec;
    int size;
    adjmat_t *result;

    ec = rnginput(&size, 1, INT_MAX);
    if (ec)
    {
        return ec;
    }
    adjmat_t *matrix = amcreate(size);
    ec = amfill(stdin, matrix);
    if (ec)
    {
        return 1;
    }

    result = cutgraph(*matrix);

    if (result)
    {
        gvexport(*matrix, *result);
        return 0;
    }

    return 1;
}