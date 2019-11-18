#ifndef __LISTSTACK_H__
#define __LISTSTACK_H__

#include "include/array.h"
typedef struct liststack
{
    int data;
    struct liststack *next;
} liststack_t;

liststack_t *create_node(const int data);

int is_fulll(liststack_t *root, size_t limit);

int is_emptyl(liststack_t *root);

int pushl(liststack_t **root, const int data, size_t limit);

int popl(liststack_t **root, arr_t *arr);

int free_stackl(liststack_t **root, arr_t *arr);

#endif