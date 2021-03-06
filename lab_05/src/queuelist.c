#include <errno.h>

#include "include/rc.h"
#include "include/queuelist.h"

/*
Queue node creation.

Input data:
* const int item - queue item.

Output data:
* node - pointer to created node.
*/
queuenode_t *create_queuenode(const task_t task)
{
    queuenode_t *node = (queuenode_t *)malloc(sizeof(queuenode_t));
    if (!node)
    {
        return NULL;
    }
    node->task.num = task.num;
    node->task.time_out = task.time_out;
    node->next = NULL;

    return node;
}

/*
Queue on linked list creation.

Output data:
* queue - pointer to created empty queue.
*/
queuelist_t *create_queuelist(const unsigned capacity)
{
    queuelist_t *queue = (queuelist_t *)malloc(sizeof(queuelist_t));
    if (!queue)
    {
        return NULL;
    }
    queue->rear = NULL;
    queue->front = NULL;
    queue->size = 0;
    queue->capacity = capacity;

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
Check queue overflow.

Input data:
* queuelist_t *const queue - pointer to queue.

Output data:
* Binary sign - 1 if empty, 0 - otherwise.
*/
int is_fulllist(queuelist_t *const queue)
{
    return queue->size == queue->capacity;
}

/*
Add item to queue.

Input data:
* queuelist_t *const queue - pointer to queue.
* const int item - item to be added.
*/
void enqueuelist(queuelist_t *const queue, const task_t task)
{
    queuenode_t *node = create_queuenode(task);

    if (is_fulllist(queue))
    {
        errno = EQUEUEOVERFLOW;
        return;
    }

    if (queue->rear == NULL)
    {
        queue->front = node;
        queue->rear = node;
        queue->size++;
        return;
    }

    queue->rear->next = node;
    queue->rear = node;
    queue->size++;
}

/*
Get item from queue.

Input data:
* queulist_t *const queue - pointer to queue.
* arr_t *const fmem - pointer to fmem slices array.

Output data:
* Got data.
*/
task_t dequeuelist(queuelist_t *const queue, arr_t *const fmem)
{
    task_t task = {.time_out = 0, .num = 0};
    if (queue->front == NULL)
    {
        errno = EQUEUEEMPTY;
        return task;
    }

    queuenode_t *node = queue->front;
    fmem->arr[++fmem->ind] = (size_t)node;
    task = node->task;

    if (queue->front == queue->rear)
    {
        queue->rear = NULL;
        queue->front = NULL;
    }
    else
    {
        queue->front = queue->front->next;
    }

    free(node);

    queue->size--;

    return task;
}

/*
Free memory allocated for queue.

Input data:
* queulist_t *const queue - pointer to queue.
* arr_t *const fmem - pointer to fmem slices array.
*/
void freequeuelist(queuelist_t *queue, arr_t *const fmem)
{
    if (queue == NULL)
    {
        return;
    }

    while (!is_emptylist(queue))
    {
        dequeuelist(queue, fmem);
    }

    free(queue);
}

/*
Check queue's rear's address existance in fmem array and delete if so.

Input data:
* queuelist_t *queue - queue realization.
* arr_t *fmem - free memory slices.

Output data:
* Binary sign - 1 if address present, 0 otherwise.
*/
int check_rear(queuelist_t *queue, arr_t *fmem)
{
    size_t top = (size_t)queue->rear;
    int is_found = 0;

    for (int i = 0; i < fmem->ind; ++i)
    {
        if (top == fmem->arr[i])
        {
            is_found = 1;
            for (int j = i; j < fmem->ind - 1; ++j)
            {
                size_t temp = fmem->arr[j];
                fmem->arr[j] = fmem->arr[j + 1];
                fmem->arr[j + 1] = temp;
            }
        }
    }

    if (is_found)
    {
        fmem->ind--;
    }

    return is_found;
}