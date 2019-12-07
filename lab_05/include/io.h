#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <errno.h>

#include "include/rc.h"
#include "include/macro.h"

void welcome();

void clean_input_stream();

void input_interval(int *const num, const int left, const int right);

#endif