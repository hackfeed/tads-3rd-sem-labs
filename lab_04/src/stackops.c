#include <stdio.h>
#include <math.h>

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
* Decreasing subsequences.
*/
void decsubseq_arr(arrstack_t *stack)
{
    int el = popa(stack);

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
            for (int j = 0; j < i; ++j)
            {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }

        free(arr);
    }
}

/*
Find decreasing subsequence of sequence in stack. 
Linkedlist-based stack implementation.

Input data:
* liststack_t **root - pointer to stack root.
* arr_t *const fmem - free memory slices.

Output data:
* Decreasing subsequences.
*/
void decsubseq_list(liststack_t **root, arr_t *const fmem)
{
    int el = popl(root, fmem);

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
            for (int j = 0; j < i; ++j)
            {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }

        free(arr);
    }
}
