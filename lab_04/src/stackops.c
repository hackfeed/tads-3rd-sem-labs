#include <stdio.h>
#include <inttypes.h>

#include "include/rc.h"
#include "include/array.h"
#include "include/arrstack.h"
#include "include/liststack.h"

/*
Find decreasing subsequence of sequence in stack. 
Array-based stack implementation.

Input data:
* arrstack_t *stack - stack.

Output data:
* Amount of decreasing subsequences.
*/
int decsubseq_arr(arrstack_t *stack)
{
    int el = popa(stack);
    int count = 0;

    while (!is_emptya(stack))
    {
        int *arr = (int *)malloc(stack->capacity * sizeof(int));
        int new_el = popa(stack);

        arr[0] = el;
        int i = 1;

        while (new_el > el)
        {
            arr[i] = new_el;
            i++;
            el = new_el;
            if (!is_emptya(stack))
            {
                new_el = popa(stack);
            }
        }
        el = new_el;

        if (i != 1)
        {
            count++;

            for (int j = 0; j < i; ++j)
            {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }

        free(arr);
    }

    return count;
}

/*
Find decreasing subsequence of sequence in stack. 
Linkedlist-based stack implementation.

Input data:
* liststack_t **root - pointer to stack root.
* arr_t *const fmem - free memory slices.

Output data:
* Amount of decreasing subsequences.
*/
int decsubseq_list(liststack_t **root, arr_t *const fmem)
{
    int el = popl(root, fmem);
    int count = 0;

    while (!is_emptyl(*root))
    {
        int *arr = (int *)malloc(fmem->capacity * sizeof(int));
        int new_el = popl(root, fmem);

        arr[0] = el;
        int i = 1;

        while (new_el > el)
        {
            arr[i] = new_el;
            i++;
            el = new_el;
            if (!is_emptyl(*root))
            {
                new_el = popl(root, fmem);
            }
        }
        el = new_el;

        if (i != 1)
        {
            count++;

            for (int j = 0; j < i; ++j)
            {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }

        free(arr);
    }

    return count;
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
