#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

#include "rc.h"
#include "macro.h"

void welcome();

void clinstream();

int rnginput(int *const num, const int left, const int right);

#endif