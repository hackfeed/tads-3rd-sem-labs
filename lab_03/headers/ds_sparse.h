#ifndef __DS_SPARSE_H__
#define __DS_SPARSE_H__

/*
CDIO headers.
*/

#include "data_structures.h"

void fill_sparse(sparse_t *const sparse);

int screate(sparse_t *const sparse, const int dots, const int cols);

int sdelete(sparse_t *const sparse);

int sinput(sparse_t *const sparse, const matrix_t matrix);

int soutput(const sparse_t sparse);

#endif