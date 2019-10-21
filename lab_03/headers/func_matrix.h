/*
Matrix handling module's headers.
*/

#ifndef __FUNC_MATRIX_H__
#define __FUNC_MATRIX_H__

#include <inttypes.h>

#include "data_structures.h"

void classic_sum(const matrix_t matrix_a, const matrix_t matrix_b, matrix_t *const matrix_res);

int sdots(const sparse_t sparse_a, const sparse_t sparse_b, int *const dots);

uint64_t tick(void);

#endif