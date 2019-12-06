#ifndef __QUEUELIST_H__
#define __QUEUELIST_H__

#include <stdlib.h>
#include "include/array.h"

typedef struct queuenode
{
    int item;
    int ind;
    struct queuenode *next;
} queuenode_t;

typedef struct
{
    queuenode_t *front, *rear;
} queuelist_t;

queuenode_t *create_queuenode(const int item);

queuelist_t *create_queuelist();

int is_emptylist(queuelist_t *const queue);

void enqueuelist(queuelist_t *const queue, const int item);

int dequeuelist(queuelist_t *const queue, arr_t *const fmem);

void freequeuelist(queuelist_t *queue, arr_t *const fmem);

#endif