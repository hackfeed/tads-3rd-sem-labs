#ifndef __QUEUEOPS_H__
#define __QUEUEOPS_H__

#include <stdio.h>
#include <inttypes.h>

#include "include/rc.h"
#include "include/macro.h"

#include "include/array.h"
#include "include/queuearr.h"
#include "include/queuelist.h"
#include "include/utils.h"

void list_model(queuelist_t *const queue, arr_t *const fmem,
                const int llim_in, const int rlim_in,
                const int llim_out, const int rlim_out,
                const int repeats);

void array_model(queuearr_t *const queue,
                 const int llim_in, const int rlim_in,
                 const int llim_out, const int rlim_out,
                 const int repeats);

#endif