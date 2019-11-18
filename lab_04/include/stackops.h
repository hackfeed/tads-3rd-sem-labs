#ifndef __STACKOPS_H__
#define __STACKOPS_H__

#include "include/arrstack.h"
#include "include/liststack.h"

void decsubseq_arr(arrstack_t *stack);

void decsubseq_list(liststack_t **root, const int capacity);

#endif