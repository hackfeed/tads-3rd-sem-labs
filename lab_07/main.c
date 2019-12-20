#include "include/combinatorics.h"
#include "include/utils.h"

int main()
{
    int ec;
    int size;
    adjmat_t *result;

    welcome();

    printf(ANSI_COLOR_GREEN
           "Введите число вершин графа: " ANSI_COLOR_RESET);
    ec = rnginput(&size, 1, INT_MAX);
    if (ec)
    {
        printf(ANSI_COLOR_RED
               "Введено недопустимое значение! Повторите попытку.\n" ANSI_COLOR_RESET);
        return ec;
    }

    adjmat_t *matrix = amcreate(size);
    printf(ANSI_COLOR_GREEN
           "Введите связи в графе (в формате 'номер_вершины номер_вершины').\n"
           "Для завершения ввода введите '-1' (нумерация вершин начинается с 0):\n" ANSI_COLOR_RESET);
    ec = amfill(stdin, matrix);
    if (ec)
    {
        if (ec == EINVALIDINTEGER || ec == EINVALIDRANGE)
        {
            printf(ANSI_COLOR_RED
                   "Введено недопустимое значение! Повторите попытку.\n" ANSI_COLOR_RESET);
            amfree(matrix);
            return ec;
        }
        if (ec == EINVALIDVERTEXPAIR)
        {
            printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,
                   "Путь в себя невозможен!");
            amfree(matrix);
            return ec;
        }
    }

    uint64_t start, end, time;
    start = tick();
    result = cutgraph(*matrix);
    end = tick();
    time = end - start;

    if (result)
    {
        printf(ANSI_COLOR_YELLOW
               "Удаленные рёбра на графе отмечены красным цветом!\n" ANSI_COLOR_RESET);
        gvexport(*matrix, *result);
        printf(ANSI_COLOR_YELLOW
               "Время выполнения алгоритма: %ju" ANSI_COLOR_RESET,
               time);
        amfree(matrix);
        amfree(result);
        return EOK;
    }
    printf(ANSI_COLOR_YELLOW
           "Невозможно сделать граф несвязным!\n" ANSI_COLOR_RESET);
    amfree(matrix);
    amfree(result);

    return EOK;
}