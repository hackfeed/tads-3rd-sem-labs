#include "include/utils.h"

/*
Get abstract time value.

Input data:
* const int llim, rlim - abstract time limits.

Output data:
* Calculated time.
*/
double get_time(const int llim, const int rlim)
{
    double rnd = (double)rand() / (double)RAND_MAX;

    return (rlim - llim) * rnd + llim;
}

/*
Processor's tick counter.

Output data:
* ticks - processor's ticks until return statement.
*/
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}