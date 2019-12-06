#include "include/queueops.h"

void list_model(queuelist_t *const queue, arr_t *const fmem,
                const int llim_in, const int rlim_in,
                const int llim_out, const int rlim_out,
                const int repeats)
{
    int in_tasks = 0;
    int out_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double hold_time = 0;

    double time_in = get_time(llim_in, rlim_in);
    double time_out = -1;

    task_t task_todo;

    int reusedmem = 0;
    int newmem = 0;
    int which;

    while (out_tasks != 1000)
    {
        if (time_out < 0 || time_in < time_out)
        {
            if (time_out < 0)
            {
                hold_time += time_in;
            }

            service_time += time_in;
            time_out -= time_in;
            time_in = get_time(llim_in, rlim_in);

            task_t task = {.num = 0,
                           .time_out = get_time(llim_out, rlim_out)};

            enqueuelist(queue, task);

            which = check_rear(queue, fmem);
            if (which)
            {
                reusedmem++;
            }
            else
            {
                newmem++;
            }

            in_tasks++;

            if (time_out < 0)
            {
                task_todo = dequeuelist(queue, fmem);
                time_out = task_todo.time_out;
            }
        }
        else
        {
            time_in -= time_out;
            service_time += time_out;
            time_out = 0;

            task_todo.num++;
            calls++;

            if (task_todo.num < repeats)
            {
                task_todo.time_out = get_time(llim_out, rlim_out);
                enqueuelist(queue, task_todo);

                which = check_rear(queue, fmem);
                if (which)
                {
                    reusedmem++;
                }
                else
                {
                    newmem++;
                }
            }
            else
            {
                out_tasks++;
            }

            if (is_emptylist(queue))
            {
                time_out = -1;
            }
            else
            {
                task_todo = dequeuelist(queue, fmem);
                time_out = task_todo.time_out;
            }
        }
    }

    printf("Рабочее время автомата: %lf\n"
           "Число вошедших заявок: %d\n"
           "Число вышедших заявок: %d\n"
           "Число срабатываний автомата: %d\n"
           "Время простоя автомата: %lf\n"
           "Количество адресов, взятых из использованной памяти: %d\n"
           "Количество адресов, взятых из новой памяти: %d\n",
           service_time, in_tasks, out_tasks, calls, hold_time, reusedmem, newmem);
}