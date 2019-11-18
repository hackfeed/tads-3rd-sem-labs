#ifndef __STACKOPS_H__
#define __STACKOPS_H__

#include <inttypes.h>

#include "include/arrstack.h"
#include "include/liststack.h"

int decsubseq_arr(arrstack_t *stack);

int decsubseq_list(liststack_t **root, const int capacity);

uint64_t tick(void);

#endif