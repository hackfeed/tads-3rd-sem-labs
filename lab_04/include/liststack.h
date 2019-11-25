#ifndef __LISTSTACK_H__
#define __LISTSTACK_H__

#include "include/array.h"
typedef struct liststack
{
    int data;
    int ind;
    struct liststack *next;
} liststack_t;

liststack_t *create_node(const int data);

int is_fulll(liststack_t *root, const int limit);

int is_emptyl(liststack_t *root);

int pushl(liststack_t **root, const int data, const int limit);

int input_stackl(const int count, liststack_t **root, const int limit);

int output_stackl(liststack_t *root);

void check_top(liststack_t *root, arr_t *fmem);

int popl(liststack_t **root, arr_t *fmem);

int free_stackl(liststack_t **root, arr_t *fmem);

#endif