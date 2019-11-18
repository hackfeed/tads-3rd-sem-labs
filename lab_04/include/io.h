#ifndef __IO_H__
#define __IO_H__

#include "include/arrstack.h"
#include "include/liststack.h"

void welcome();

void clean_input_stream();

int input_interval(int *const num, const int left, const int right);

int input_stack(const int count, arrstack_t *stack, liststack_t **root, const int limit);

int pop_stack(arrstack_t *stack, liststack_t **root, arr_t *const arr);

#endif