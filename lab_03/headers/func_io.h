/*
IO module headers.
*/

#ifndef __FUNC_IO_H__
#define __FUNC_IO_H__

#include "data_structures.h"
#include "defines.h"

void welcome();

void clean_input_stream();

int input_interval(int *const num, const int left, const int right);

#endif