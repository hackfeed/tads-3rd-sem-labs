#include <stdio.h>
#include <inttypes.h>

#include "include/rc.h"
#include "include/array.h"
#include "include/arrstack.h"
#include "include/liststack.h"
#include "include/io.h"
#include "include/stackops.h"

int main()
{
    int limit = 0xFFFFFFFF;
    int capacity;
    arr_t *arr = NULL;
    liststack_t *root = NULL;
    arrstack_t *stack = NULL;

    welcome();

    input_interval(&capacity, 1, INT64_MAX);
    arr = create_array(capacity);
    stack = create_stacka(capacity);
    input_stack(capacity, stack, &root, limit);
    decsubseq_list(&root, arr);
    output_array(*arr);
    free_stacka(stack);
    free_stackl(&root, arr);
    free_array(arr);

    return OK;
}