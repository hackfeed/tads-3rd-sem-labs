#include "include/rc.h"
#include "include/queuelist.h"

/*
Queue node creation.

Input data:
* const int item - queue item.

Output data:
* node - pointer to created node.
*/
queuenode_t *create_queuenode(const int item)
{
    queuenode_t *node = (queuenode_t *)malloc(sizeof(queuenode_t));
    if (!node)
    {
        return NULL;
    }
    node->item = item;
    node->ind = 0;
    node->next = NULL;

    return node;
}

/*
Queue on linked list creation.

Output data:
* queue - pointer to created empty queue.
*/
queuelist_t *create_queuelist()
{
    queuelist_t *queue = (queuelist_t *)malloc(sizeof(queuelist_t));
    if (!queue)
    {
        return NULL;
    }
    queue->rear = NULL;
    queue->front = NULL;
    
    return queue;
}

/*
Check queue emptiness.

Input data:
* queuelist_t *const queue - pointer to queue.

Output data:
* Binary sign - 1 if empty, 0 - otherwise.
*/
int is_emptylist(queuelist_t *const queue)
{
    return queue->rear == NULL;
}

/*
Add item to queue.

Input data:
* queuelist_t *const queue - pointer to queue.
* const int item - item to be added.
*/
void enqueuelist(queuelist_t *const queue, const int item)
{
    queuenode_t *node = create_queuenode(item);

    if (queue->rear == NULL)
    {
        queue->front = node;
        queue->rear = node;

        return;
    }

    node->ind = queue->rear->ind + 1;
    queue->rear->next = node;
    queue->rear = node;
}

/*
Get item from queue.

Input data:
* queulist_t *const queue - pointer to queue.
* arr_t *const fmem - pointer to fmem slices array.

Output data:
* Got data.
*/
int dequeuelist(queuelist_t *const queue, arr_t *const fmem)
{
    if (queue->front == NULL)
    {
        return NULL;
    }

    queuenode_t *node = queue->front;
    fmem->arr[++fmem->ind] = node;
    int data = node->item;

    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(node);

    return data;
}

/*
Free memory allocated for queue.

Input data:
* queulist_t *const queue - pointer to queue.
* arr_t *const fmem - pointer to fmem slices array.
*/
void freequeuelist(queuelist_t *queue, arr_t *const fmem)
{
    while (!is_emptylist(queue))
    {
        dequeuelist(queue, fmem);
    }

    free(queue);
}

/*
Check root's address existance in fmem array and delete if so.

Input address:
* liststack_t *root - stack realization.
* arr_t *fmem - free memory slices.
*/
// void check_top(liststack_t *root, arr_t *fmem)
// {
//     size_t top = root;

//     for (int i = 0; i < fmem->ind; ++i)
//     {
//         if (top == fmem->arr[i])
//         {
//             for (int j = i; j < fmem->ind - 1; ++j)
//             {
//                 size_t temp = fmem->arr[j];
//                 fmem->arr[j] = fmem->arr[j + 1];
//                 fmem->arr[j + 1] = temp;
//             }
//         }
//     }

//     fmem->ind--;
// }