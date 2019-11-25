#ifndef __IO_H__
#define __IO_H__

#include "include/arrstack.h"
#include "include/liststack.h"

void welcome();

void clean_input_stream();

int input_interval(int *const num, const int left, const int right);

#endif