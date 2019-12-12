#include "include/io.h"

void welcome()
{
    printf("%s",
           ANSI_COLOR_GREEN
           "d888888b d8888b. d88888b d88888b \n"
           "`~~88~~' 88  `8D 88'     88'     \n"
           "   88    88oobY' 88ooooo 88ooooo \n"
           "   88    88`8b   88~~~~~ 88~~~~~ \n"
           "   88    88 `88. 88.     88.     \n"
           "   YP    88   YD Y88888P Y88888P\n\n" ANSI_COLOR_RESET);
    printf("%s",
           ANSI_COLOR_MAGENTA
           "Данная программа позволяет построить ДДП, сбалансированное двоичное дерево \n"
           "и хеш-таблицу по указанным данным, вывести на экран дерево в виде дерева, \n"
           "провести реструктуризацию хеш-таблицы, если среднее количество сравнений \n"
           "больше указанного, вывести количественную характеристику моделирования. \n\n" ANSI_COLOR_RESET);
}
