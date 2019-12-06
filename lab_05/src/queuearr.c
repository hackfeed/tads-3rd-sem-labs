#include "include/rc.h"
#include "include/queuearr.h"

/*
Queue on array creation.

Input data:
* const unsigned capacity - queue capacity.

Output data:
* queue - pointer to created queue.
*/
queuearr_t *create_queuearr(const unsigned capacity)
{
    queuearr_t *queue = (queuearr_t *)malloc(sizeof(queuearr_t));
    if (!queue)
    {
        return NULL;
    }
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity - 1;
    queue->arr = (int *)malloc(queue->capacity * sizeof(int));
    if (!queue->arr)
    {
        free(queue);
        return NULL;
    }

    return queue;
}

/*
Check queue overflow.

Input data:
* queuearr_t *const queue - pointer to queue.

Output data:
* Binary sign - 1 if full, 0 - otherwise.
*/
int is_fullarr(queuearr_t *const queue)
{
    return queue->size == queue->capacity;
}

/*
Check queue emptiness.

Input data:
* queuearr_t *const queue - pointer to queue.

Output data:
* Binary sign - 1 if empty, 0 - otherwise.
*/
int is_emptyarr(queuearr_t *const queue)
{
    return queue->size == 0;
}

/*
Add item to queue.

Input data:
* queuearr_t *const queue - pointer to queue.
* const int item - item to be added.
*/
void enqueuearr(queuearr_t *const queue, const int item)
{
    if (is_fullarr(queue))
    {
        errno = EQUEUEOVERFLOW;
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = item;
    queue->size++;
}

/*
Get item from queue.

Input data:
* queuearr_t *const queue - pointer to queue.

Output data:
* Got data.
*/
int dequeuearr(queuearr_t *const queue)
{
    if (is_emptyarr(queue))
    {
        errno = EQUEUEEMPTY;
        return INT_MIN;
    }
    int item = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return item;
}

/*
Free memory allocated for queue.

Input data:
* queuearr_t *queue - pointer to queue.
*/
void freequeuearr(queuearr_t *queue)
{
    if (queue)
    {
        if (queue->arr)
        {
            free(queue->arr);
            free(queue);
            errno = EOK;

            return;
        }

        free(queue);
        errno = EOK;

        return;
    }

    errno = EARRAYMEMORY;
}