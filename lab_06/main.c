#include "include/tree_utils.h"
#include "include/list_utils.h"
#include "include/hash_utils.h"
#include "include/search.h"
#include "include/timer.h"
#include "include/io.h"

int main(int argc, char *argv[])
{
    welcome();

    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf(ANSI_COLOR_RED
               "Неверное имя файла! Повторите попытку.\n" ANSI_COLOR_RESET);
        return FILE_ERROR;
    }

    if (fgetc(f) == EOF)
    {
        printf(ANSI_COLOR_RED
               "Файл пуст! Проверьте файл.\n" ANSI_COLOR_RESET);
        return FILE_ERROR;
    }

    rewind(f);

    char **words = fill_words(f);
    unsigned long flen = file_len(f);
    tree_node *root = NULL;

    uint64_t time = tick();
    fill_tree(&root, f);
    time = tick() - time;

    printf(ANSI_COLOR_YELLOW
           "БИНАРНОЕ ДЕРЕВО НА ОСНОВЕ ДАННЫХ ИЗ ФАЙЛА:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN);
    print_tree(root, 0);
    printf(ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA
           "Дерево построено за = %ld тактов процессора "
           "(в данное время включено время чтения из файла).\n\n" ANSI_COLOR_RESET,
           time);

    int unique;
    time = tick();
    root = balance_tree(root, &unique);
    time = tick() - time;
    printf(ANSI_COLOR_YELLOW
           "БИНАРНОЕ ДЕРЕВО ПОСЛЕ БАЛАНСИРОВКИ:\n" ANSI_COLOR_YELLOW);
    printf(ANSI_COLOR_GREEN);
    print_tree(root, 0);
    printf(ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA
           "Дерево сбалансировано за = %ld тактов процессора.\n\n" ANSI_COLOR_RESET,
           time);

    int n = file_len(f);
    list_t *hash_list = calloc(n, sizeof(list_t));
    int cmpr, desired_cmpr;

    int (*hash)(char *, int);

    time = tick();
    unsafe_hash("chill", 10);
    time = tick() - time;
    printf(ANSI_COLOR_YELLOW
           "%ld - генерация простой хеш-функции (в тактах процессора).\n" ANSI_COLOR_RESET,
           time);

    time = tick();
    safe_hash("chill", 10);
    time = tick() - time;
    printf(ANSI_COLOR_GREEN
           "%ld - генерация сложной хеш-функции (в тактах процессора).\n" ANSI_COLOR_RESET,
           time);

    hash = &unsafe_hash;
    time = tick();
    cmpr = build_hash_table(&hash_list, n, f, hash);
    time = tick() - time;

    printf(ANSI_COLOR_YELLOW
           "\nХЕШ-ТАБЛИЦА НА ОСНОВЕ ПРОСТОЙ ФУНКЦИИ:" ANSI_COLOR_RESET);
    print_hash_table(hash_list, n);
    printf(ANSI_COLOR_MAGENTA
           "Максимальное количество коллизий = %d.\n" ANSI_COLOR_RESET,
           cmpr);
    printf(ANSI_COLOR_MAGENTA
           "Хеш-таблица построена за = %ld тактов процессора "
           "(в данное время включено время чтения из файла).\n\n" ANSI_COLOR_RESET,
           time);

    printf("\nВведите допустимое количество коллизий: ");
    int ec = scanf("%d", &desired_cmpr);
    if (ec != 1)
    {
        printf(ANSI_COLOR_RED "Введено неверное значение!\n" ANSI_COLOR_RESET);

        return VAL_ERROR;
    }

    if (cmpr > desired_cmpr)
    {
        while (cmpr != desired_cmpr)
        {
            free_list_arr(hash_list, n);
            n = next_prime(n);
            hash_list = calloc(n, sizeof(list_t));

            hash = &safe_hash;
            time = tick();
            cmpr = build_hash_table(&hash_list, n, f, hash);
            time = tick() - time;
        }
        printf(ANSI_COLOR_GREEN
               "\nХЕШ-ТАБЛИЦА НА ОСНОВЕ УЛУЧШЕННОЙ ФУНКЦИИ:" ANSI_COLOR_RESET);
        print_hash_table(hash_list, n);
        printf(ANSI_COLOR_MAGENTA
               "Количество коллизий = %d.\n" ANSI_COLOR_RESET,
               cmpr);
        printf(ANSI_COLOR_MAGENTA
               "Хеш-таблица построена за = %ld тактов процессора "
               "(в данное время включено время чтения из файла).\n\n" ANSI_COLOR_RESET,
               time);
    }
    else
    {
        printf(ANSI_COLOR_GREEN
               "Результат достижим за введенное количество коллизий.\n"
               "Пересоздание таблицы не требуется.\n" ANSI_COLOR_RESET);
    }

    char to_find[STR_SIZE];
    printf("\nВведите слово которое хотите найти: ");
    scanf("%s", to_find);

    int depth = 0;
    int vrtxs = 0;
    int cmprs = 0;
    tree_node *root2 = NULL;
    fill_tree(&root2, f);
    time = tick();
    ec = search_tree(to_find, *root2);
    time = tick() - time;
    tree_depth(root2, &vrtxs, &cmprs, depth);
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В БИНАРНОМ ДЕРЕВЕ\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов процессора.\n"
               "Среднее время поиска в бинарном дереве - %lf тактов процессора.\n"
               "Бинарное дерево занимает - %ld байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time, search_tree_av(*root2, words, flen),
               unique * sizeof(tree_node), ec,
               (double)cmprs / vrtxs);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }
    free_tree(root2);

    depth = 0;
    vrtxs = 0;
    cmprs = 0;
    time = tick();
    ec = search_tree(to_find, *root);
    time = tick() - time;
    tree_depth(root, &vrtxs, &cmprs, depth);
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В БИНАРНОМ СБАЛАНСИРОВАННОМ ДЕРЕВЕ\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов процессора.\n"
               "Среднее время поиска в бинарном сбалансированном дереве - %lf тактов процессора.\n"
               "Бинарное сбалансированное дерево занимает - %ld байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time, search_tree_av(*root, words, flen),
               unique * sizeof(tree_node), ec,
               (double)cmprs / vrtxs);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }
    free_tree(root);

    time = tick();
    ec = search_hashtable(to_find, hash_list, n, hash);
    time = tick() - time;
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В ХЕШ-ТАБЛИЦЕ\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов процессора.\n"
               "Среднее время поиска в хеш-таблице - %lf тактов процессора.\n"
               "Хеш-таблица занимает - %ld байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time / 4, search_hashtable_av(hash_list, n, hash, words, flen),
               (n + unique - list_occupation(hash_list, n)) * sizeof(list_t) + sizeof(list_t *), ec,
               (double)(1 + desired_cmpr) / 2);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }
    free_list_arr(hash_list, n);

    time = tick();
    ec = search_file(to_find, f);
    time = tick() - time;
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В ФАЙЛЕ\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов процессора.\n"
               "Среднее время поиска в файле - %lf тактов процессора.\n"
               "Файл занимает - %u байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time, search_file_av(f, words, flen),
               fbytes(f), ec, (double)file_len(f) / 2);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }

    fclose(f);

    return OK;
}