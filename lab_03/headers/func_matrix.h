#ifndef __FUNC_MATRIX_H__
#define __FUNC_MATRIX_H__

/*
Matrix handling module's headers (both sparse and classic).
*/

#include <inttypes.h>

#include "data_structures.h"

void classic_sum(const matrix_t matrix_a, const matrix_t matrix_b, matrix_t *const matrix_res, uint64_t *const ticks);

int sdots(const sparse_t sparse_a, const sparse_t sparse_b, int *const dots);

int arrays_min(type_t *a_arr, const int a_len, type_t *b_arr, const int b_len);

void sparse_sum(const sparse_t sparse_a, const sparse_t sparse_b, sparse_t *const sparse_res, uint64_t *const ticks);

int fill_col_entry(sparse_t *const sparse, const matrix_t matrix);

uint64_t tick(void);

int random(const int offset);

void gorandom(matrix_t *const matrix, int percent);

#endif