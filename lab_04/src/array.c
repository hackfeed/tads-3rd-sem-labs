#include <stdio.h>
#include <stdlib.h>

#include "include/rc.h"
#include "include/array.h"

/*
Create array.

Input data:
* const int capacity - array capacity.

Output data:
* arr - pointer to created array.
*/
arr_t *create_array(const int capacity)
{
    arr_t *arr = (arr_t *)malloc(sizeof(arr_t));
    if (!arr)
    {
        return NULL;
    }

    arr->capacity = capacity;
    arr->ind = -1;
    arr->arr = (size_t *)malloc(arr->capacity * sizeof(size_t));

    return arr;
}

/*
Output filled array to ind element.
*/
void output_array(const arr_t arr)
{
    if (arr.ind == -1)
    {
        printf("%s", "Массив пуст");
    }
    else
    {
        for (int i = 0; i < arr.ind + 1; ++i)
        {
            printf("%zx ", arr.arr[i]);
        }
    }

    printf("\n");
}

/*
Free memory allocated for array.

Input data:
* arr_t *arr - array to be freed.

Output data:
* Return code - OK or ARRAY_MEMORY_ERROR.
*/
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