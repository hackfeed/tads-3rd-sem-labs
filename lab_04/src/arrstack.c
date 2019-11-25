/*
Stack realization based on array.
*/

#include <stdlib.h>

#include "include/rc.h"
#include "include/macro.h"
#include "include/arrstack.h"

/*
Stack on array creation.

Input data:
* const int capacity - stack capacity.

Output data:
* stack - pointer to created stack.
*/
arrstack_t *create_stacka(const int capacity)
{
    arrstack_t *stack = (arrstack_t *)malloc(sizeof(arrstack_t));
    if (!stack)
    {
        return NULL;
    }

    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int *)malloc(stack->capacity * sizeof(int));
    if (!stack->arr)
    {
        free(stack);
        return NULL;
    }

    return stack;
}

/*
Check stack overflow.

Input data:
* arrstack_t *stack - pointer to stack.

Output data:
* Binary sign - 1 if full, 0 - otherwise.
*/
int is_fulla(arrstack_t *stack)
{
    return stack->top == stack->capacity - 1;
}

/*
Check stack emptiness.

Input data:
* arrstack_t *stack - pointer to stack.

Output data:
* Binary sign - 1 if empty, 0 - otherwise.
*/
int is_emptya(arrstack_t *stack)
{
    return stack->top == -1;
}

/*
Push item to stack.

Input data:
* arrstack_t *stack - pointer to stack.
* const int data - item to be pushed.

Output data:
* Return code - OK or STACK_OVERFLOW.
*/
int pusha(arrstack_t *stack, const int data)
{
    if (is_fulla(stack))
    {
        return STACK_OVERFLOW;
    }

    stack->arr[++stack->top] = data;

    return OK;
}

/*
Input stack based on array.

Input data:
* const int count - count of stack elements.
* arrstack_t *stack - stack realizations.

Output data:
* Return code - OK, STACK_OVERFLOW or INVALID_INT_INPUT_ERROR.
*/
int input_stacka(const int count, arrstack_t *stack)
{
    int el;

    for (int i = 0; i < count; ++i)
    {
        if (scanf("%d", &el) != GOT_ARG)
        {
            clean_input_stream();
            return INVALID_INT_INPUT_ERROR;
        }

        if (pusha(stack, el))
        {
            return STACK_OVERFLOW;
        }
    }

    return OK;
}

/*
Output stack based on array.

Input data:
* arrstack_t *stack - stack realization.

Output data:
* Return code - OK or STACK_EMPTY.
*/
int output_stacka(arrstack_t *stack)
{
    if (is_emptya(stack))
    {
        return STACK_EMPTY;
    }

    int size = stack->top;

    while (size >= 0)
    {
        printf("%d\n", stack->arr[size--]);
    }

    return OK;
}

/*
Pop data from stack.

Input data:
* arrstack_t *stack - pointer to stack.

Output data:
* Return code - STACK_EMPTY.
* Popped data.
*/
int popa(arrstack_t *stack)
{
    if (is_emptya(stack))
    {
        return STACK_EMPTY;
    }

    return stack->arr[stack->top--];
}

/*
Free memory allocated for stack.

Input data:
* arrstack_t *stack - pointer to stack.

Output data:
* Return code - OK or STACK_MEMORY_ERROR.
*/
int free_stacka(arrstack_t *stack)
{
    if (stack)
    {
        if (stack->arr)
        {
            free(stack->arr);
            free(stack);

            return OK;
        }

        free(stack);

        return OK;
    }

    return STACK_MEMORY_ERROR;
}