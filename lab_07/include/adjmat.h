#ifndef __ADJMAT_H__
#define __ADJMAT_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "io.h"

typedef struct
{
    int size;
    int **matrix;
} adjmat_t;

adjmat_t *amcreate(const int size);

void amfree(adjmat_t *matrix);

adjmat_t *amcopy(adjmat_t matrix);

int amfill(FILE *const stream, adjmat_t *const matrix);

void amouptut(FILE *const stream, const adjmat_t matrix);

void dfs(const adjmat_t matrix, const int vertex, int *visited);

#endif