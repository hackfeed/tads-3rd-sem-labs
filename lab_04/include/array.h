#ifndef __ARRAY_H__
#define __ARRAY_H__

typedef struct
{
    size_t *arr;
    int capacity;
    int ind;
} arr_t;

arr_t *create_array(const int capacity);

void output_array(const arr_t arr);

int free_array(arr_t *arr);

#endif