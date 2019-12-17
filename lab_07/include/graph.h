#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>

#include "include/adjmat.h"

typedef struct
{
    int fvertex, svertex;
} edge_t;

typedef struct
{
    int size;
    edge_t *edges;
} chain_t;

chain_t *chcreate(adjmat_t matrix);

edge_t **alrows(const int n, const int m);

void gvexport(adjmat_t matrix, adjmat_t result);

#endif