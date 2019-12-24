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
    queue->arr = (task_t *)malloc(queue->capacity * sizeof(task_t));
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
* const task_t task - task to be added.
*/
void enqueuearr(queuearr_t *const queue, const task_t task)
{
    if (is_fullarr(queue))
    {
        errno = EQUEUEOVERFLOW;
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = task;
    queue->size++;
}

/*
Get item from queue.

Input data:
* queuearr_t *const queue - pointer to queue.

Output data:
* Got data.
*/
task_t dequeuearr(queuearr_t *const queue)
{
    task_t task = {.time_out = 0, .num = 0};
    if (is_emptyarr(queue))
    {
        errno = EQUEUEEMPTY;
        return task;
    }
    task = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return task;
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
}