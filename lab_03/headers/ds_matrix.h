#ifndef __DS_MATRIX_H__
#define __DS_MATRIX_H__

/*
CDIO headers.
*/

#include "data_structures.h"

int create(matrix_t *const matrix);

int deletee(matrix_t *const matrix);

int input(matrix_t *const matrix, const int dots);

int output(const matrix_t *const matrix);

#endif