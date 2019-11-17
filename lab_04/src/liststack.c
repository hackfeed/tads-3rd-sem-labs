#include <stdio.h>
#include <stdlib.h>

#include "include/rc.h"
#include "include/liststack.h"

/*
Stack on linked list creation.

Input data:
* int data - data to be written in node.

Output data:
* node - pointer to created node.
*/
liststack_t *create_node(int data)
{
    liststack_t *node = (liststack_t *)malloc(sizeof(liststack_t));
    if (!node)
    {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

/*
Check stack overflow.

Input data:
* liststack_t *root - pointer to root node.
* int limit - address limit.

Output data:
* Binary sign - 1 if full, 0 - otherwise.
*/
int is_fulll(liststack_t *root, int limit)
{
    return &root->next == limit;
}

/*
Check stack emptiness.

Input data:
* liststack_t *root - pointer to root node.

Output data:
* Binary sign - 1 if empty, 0 - otherwise.
*/
int is_emptyl(liststack_t *root)
{
    return !root;
}

/*
Push item to stack.

Input data:
* liststack_t **root - pointer to root node.
* int data - data to be pushed.
* int limit - address limit.

Output data:
* Return code - OK, STACK_OVERFLOW or STACK_MEMORY_ERROR.
*/
int pushl(liststack_t **root, int data, int limit)
{
    if (is_fulll(*root, limit))
    {
        return STACK_OVERFLOW;
    }

    liststack_t *node = create_node(data);
    if (!node)
    {
        return STACK_MEMORY_ERROR;
    }

    node->next = *root;
    *root = node;

    return OK;
}

/*
Pop data from stack.

Input data:
* liststack_t **root - pointer to root node.

Output data:
* Return code - STACK_EMPTY.
* Popped data.
*/
int popl(liststack_t **root)
{
    if (is_emptyl(*root))
    {
        return STACK_EMPTY;
    }

    liststack_t *temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);

    return popped;
}

/*
Free memory allocated for stack.

Input data:
* liststack_t **root - pointer to root node.

Output data:
* Return code - OK.
*/
int free_stackl(liststack_t **root)
{
    while (!is_emptyl(*root))
    {
        popl(root);
    }

    return OK;
}