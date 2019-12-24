#ifndef __COMBINATORICS_H__
#define __COMBINATORICS_H__

#include "graph.h"

unsigned long fact(const int num);

int combs(const int n, const int k);

void mkcombs(edge_t **ans, edge_t *tmp, chain_t chain, const int tmp_size, const int n,
             const int left, const int k, int *const idx, int *crow);

edge_t **mkcombsvect(chain_t chain, const int rows, const int n,
                     const int k, int *const idx, int *crow);

int is_conn(adjmat_t matrix);

adjmat_t *ckcut(adjmat_t matrix, edge_t **vars, const int combs, const int len);

adjmat_t *cutgraph(adjmat_t matrix);

#endif