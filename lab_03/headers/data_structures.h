/*
Data structures for table.
*/

#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include "defines.h"

#define type_spec "%d"
#define out_spec "%5d "
typedef int type_t;

typedef struct
{
    type_t **matrix;
    int rows;
    int columns;
} matrix_t;

typedef struct
{
    type_t *elems;
    int *row_entry;
    int *col_entry;
    int elems_amount;
    int cols_amount;
} sparse_t;

#endif