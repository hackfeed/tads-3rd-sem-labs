#include <stdlib.h>

#include "include/rc.h"
#include "include/array.h"

arr_t *create_array(const int capacity)
{
    arr_t *arr = (arr_t *)malloc(sizeof(arr_t));
    if (!arr)
    {
        return NULL;
    }

    arr->capacity = capacity;
    arr->ind = 0;
    arr->arr = (size_t *)malloc(arr->capacity * sizeof(size_t));

    return arr;
}

void output_array(const arr_t arr)
{
    for (int i = 0; i < arr.ind; ++i)
    {
        printf("%zx ", arr.arr[i]);
    }
    printf("\n");
}

int free_array(arr_t *arr)
{
    if (arr)
    {
        if (arr->arr)
        {
            free(arr->arr);
            free(arr);

            return OK;
        }

        free(arr);

        return OK;
    }

    return ARRAY_MEMORY_ERROR;
}