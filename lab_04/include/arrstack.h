#ifndef __ARRSTACK_H__
#define __ARRSTACK_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int top;
    int capacity;
    int *arr;
} arrstack_t;

arrstack_t *create_stacka(const int capacity);

int free_stacka(arrstack_t *stack);

int is_fulla(arrstack_t *stack);

int is_emptya(arrstack_t *stack);

int pusha(arrstack_t *stack, const int data);

int popa(arrstack_t *stack);

#endif