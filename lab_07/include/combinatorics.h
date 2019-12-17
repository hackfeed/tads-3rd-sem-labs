#ifndef __COMBINATORICS_H__
#define __COMBINATORICS_H__

#include "include/graph.h"

unsigned long fact(const int num);

int combs(const int n, const int k);

void mkcombs(edge_t **ans, edge_t *tmp, const chain_t chain, const int tmp_size, const int n,
             const int left, const int k, int *const idx, int *const crow);

edge_t **mkcombsvect(const chain_t chain, const int rows, const int n,
                     const int k, int *const idx, int *const crow);

int is_conn(const adjmat_t matrix);

adjmat_t *ckcut(adjmat_t matrix, edge_t **vars, const int combs, const int len);

adjmat_t *cutgraph(adjmat_t matrix);

#endif