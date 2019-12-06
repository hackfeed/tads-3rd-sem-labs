#ifndef __QUEUEARR_H__
#define __QUEUEARR_H__

#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef struct
{
    unsigned capacity, size, rear, front;
    int *arr;
} queuearr_t;

queuearr_t *create_queuearr(const unsigned capacity);

int is_fullarr(queuearr_t *const queue);

int is_emptyarr(queuearr_t *const queue);

void enqueuearr(queuearr_t *const queue, const int item);

int dequeuearr(queuearr_t *const queue);

void freequeuearr(queuearr_t *queue);

#endif