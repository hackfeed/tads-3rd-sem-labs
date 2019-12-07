#include "include/queueops.h"

/*
Service Automat model based on linked list.
*/
void list_model(queuelist_t *const queue, arr_t *const fmem,
                const int llim_in, const int rlim_in,
                const int llim_out, const int rlim_out,
                const int repeats)
{
    int in_tasks = 0;
    int out_tasks = 0;
    int failed_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double hold_time = 0;

    double time_in = get_time(llim_in, rlim_in);
    double time_out = -1;

    task_t task_todo;

    int reusedmem = 0;
    int newmem = 0;
    int which;

    int overall_len = 0;

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

            if (errno == EQUEUEOVERFLOW)
            {
                printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                failed_tasks++;
            }
            else
            {
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
            }

            if (time_out < 0 && queue->size)
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

                if (errno == EQUEUEOVERFLOW)
                {
                    printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                    failed_tasks++;
                }
                else
                {
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
            }
            else
            {
                overall_len += queue->size;
                out_tasks++;
                if (out_tasks % 100 == 0)
                {
                    printf(ANSI_COLOR_YELLOW
                           "\n---\n"
                           "Обработано %d заявок.\n"
                           "Длина очереди: %d\n"
                           "Средняя длина очереди: %d\n"
                           "---\n" ANSI_COLOR_RESET,
                           out_tasks, queue->size, overall_len / out_tasks);
                }
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

    double expected_time;
    if ((llim_in + rlim_in) / 2 * 1000 > (llim_out + rlim_out) / 2 * repeats * 1000)
    {
        expected_time = (llim_in + rlim_in) / 2 * 1000;
    }
    else
    {
        expected_time = calls;
    }
    double delta = fabs(service_time - expected_time) / expected_time * 100;

    printf(ANSI_COLOR_GREEN
           "Рабочее время автомата: %lf (ожидаемое рабочее время: %lf, погрешность: %lf%)\n"
           "Число вошедших заявок: %d\n"
           "Число вышедших заявок: %d\n"
           "Число необработанных заявок: %d\n"
           "Число срабатываний автомата: %d\n"
           "Время простоя автомата: %lf\n"
           "Количество адресов, взятых из использованной памяти: %d\n"
           "Количество адресов, взятых из новой памяти: %d\n" ANSI_COLOR_RESET,
           service_time, expected_time, delta, in_tasks, out_tasks, failed_tasks,
           calls, hold_time, reusedmem, newmem);
}

/*
Service Automat model based on array.
*/
void array_model(queuearr_t *const queue,
                 const int llim_in, const int rlim_in,
                 const int llim_out, const int rlim_out,
                 const int repeats)
{
    int in_tasks = 0;
    int out_tasks = 0;
    int failed_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double hold_time = 0;

    double time_in = get_time(llim_in, rlim_in);
    double time_out = -1;

    task_t task_todo;

    int overall_len = 0;

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

            enqueuearr(queue, task);

            if (errno == EQUEUEOVERFLOW)
            {
                printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                failed_tasks++;
            }
            else
            {
                in_tasks++;
            }

            if (time_out < 0 && queue->size)
            {
                task_todo = dequeuearr(queue);
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
                enqueuearr(queue, task_todo);

                if (errno == EQUEUEOVERFLOW)
                {
                    printf("Очередь переполнена! Новый элемент не будет добавлен!\n");
                    failed_tasks++;
                }
            }
            else
            {
                overall_len += queue->size;
                out_tasks++;
                if (out_tasks % 100 == 0)
                {
                    printf(ANSI_COLOR_YELLOW
                           "\n---\n"
                           "Обработано %d заявок.\n"
                           "Длина очереди: %d\n"
                           "Средняя длина очереди: %d\n"
                           "---\n" ANSI_COLOR_RESET,
                           out_tasks, queue->size, overall_len / out_tasks);
                }
            }

            if (is_emptyarr(queue))
            {
                time_out = -1;
            }
            else
            {
                task_todo = dequeuearr(queue);
                time_out = task_todo.time_out;
            }
        }
    }

    double expected_time;
    if ((llim_in + rlim_in) / 2 * 1000 > (llim_out + rlim_out) / 2 * repeats * 1000)
    {
        expected_time = (llim_in + rlim_in) / 2 * 1000;
    }
    else
    {
        expected_time = calls;
    }
    double delta = fabs(service_time - expected_time) / expected_time * 100;

    printf(ANSI_COLOR_GREEN
           "Рабочее время автомата: %lf (ожидаемое рабочее время: %lf, погрешность: %lf%)\n"
           "Число вошедших заявок: %d\n"
           "Число вышедших заявок: %d\n"
           "Число необработанных заявок: %d\n"
           "Число срабатываний автомата: %d\n"
           "Время простоя автомата: %lf\n" ANSI_COLOR_RESET,
           service_time, expected_time, delta, in_tasks, out_tasks,
           failed_tasks, calls, hold_time);
}