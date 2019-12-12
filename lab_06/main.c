#include "include/tree_utils.h"
#include "include/list_utils.h"
#include "include/hash_utils.h"
#include "include/search.h"
#include "include/timer.h"

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        fprintf(stderr, "Неверное имя файла\n");
        return FILE_ERROR;
    }

    tree_node *root = NULL;

    uint64_t time = tick();
    fill_tree(&root, f);
    time = tick() - time;

    printf("Бинарное дерево из файла\n");
    print_tree(root, 0);
    printf("Построено за = %ld тиков (в данное время включено время чтения из файла)\n\n", time);

    int unique;
    time = tick();
    root = balance_tree(root, &unique);
    time = tick() - time;
    printf("Бинарное дерево после балансировки\n");
    print_tree(root, 0);
    printf("Сбалансировано за = %ld тиков\n\n", time);

    int n = file_len(f);
    list_t *hash_list = calloc(n, sizeof(list_t));
    float cmpr, desired_cmpr;

    int (*hash)(char *, int);

    time = tick();
    unsafe_hash("sleeping", 10);
    time = tick() - time;
    printf("%ld ----- LAME HASH TIME\n", time);

    time = tick();
    safe_hash("sleeping", 10);
    time = tick() - time;
    printf("%ld ----- COOL HASH TIME\n", time);

    hash = &unsafe_hash;
    time = tick();
    cmpr = build_hash_table(&hash_list, n, f, hash);
    time = tick() - time;

    printf("\nХеш таблица простым методом");
    print_hash_table(hash_list, n);
    printf("Количество сравнений = %f\n", cmpr);
    printf("Построена за = %ld тиков (внимание, читает из файла)\n\n", time);

    printf("\nВведите желаемое количество сравнений: ");
    int ec = scanf("%f", &desired_cmpr);
    if (ec != 1)
    {
        printf("Ошибка ввода\n");

        return VAL_ERROR;
    }

    if (cmpr > desired_cmpr)
    {
        while (cmpr - desired_cmpr > 0.000001)
        {
            printf("%f \n", fabs(cmpr - desired_cmpr));
            free_list_arr(hash_list, n);
            n = next_prime(n);
            hash_list = calloc(n, sizeof(list_t));

            hash = &safe_hash;
            time = tick();
            cmpr = build_hash_table(&hash_list, n, f, hash);
            time = tick() - time;
        }
        printf("\nХеш таблица улучшенным методом");
        print_hash_table(hash_list, n);
        printf("Количество сравнений = %f\n", cmpr);
        printf("Построена за = %ld тиков (внимание, читает из файла)\n\n", time);
    }
    else
    {
        printf("Все хорошо, продолжаем\n");
    }

    char to_find[STR_SIZE];
    printf("\nВведите слово которое хотите найти: ");
    scanf("%s", to_find);

    tree_node *root2 = NULL;
    fill_tree(&root2, f);
    time = tick();
    ec = search_tree(to_find, *root2);
    time = tick() - time;
    if (ec > 0)
    {
        printf("Слово %s найдено за %ld тиков. Бинарное дерево занимает - %ld байт. Количество сравнений - %d \n",
               to_find, time,
               unique * sizeof(tree_node), ec);
    }
    else
    {
        printf("Слово %s не найдено.\n", to_find);

        return VAL_ERROR;
    }
    free_tree(root2);

    time = tick();
    ec = search_tree(to_find, *root);
    time = tick() - time;
    if (ec > 0)
    {
        printf("Слово %s найдено за %ld тиков. Бинарное сбалансированное дерево занимает - %ld байт. Количество сравнений - %d\n", to_find, time, unique * sizeof(tree_node), ec);
    }
    else
    {
        printf("Слово %s не найдено.\n", to_find);

        return VAL_ERROR;
    }
    free_tree(root);

    time = tick();
    ec = search_hashtable(to_find, hash_list, n, hash);
    time = tick() - time;
    if (ec > 0)
    {
        printf("Слово %s найдено за %ld тиков. Хэш таблица занимает - %ld байт. Количество сравнений - %d\n",
               to_find, time,
               (n + unique - list_occupation(hash_list, n)) * sizeof(list_t) + sizeof(list_t *), ec);
    }
    else
    {
        printf("Слово %s не найдено.\n", to_find);

        return VAL_ERROR;
    }
    free_list_arr(hash_list, n);

    time = tick();
    ec = search_file(to_find, f);
    time = tick() - time;
    if (ec > 0)
    {
        printf("Слово %s найдено за %ld тиков. Файловый дескриптор занимает - %ld байт. Количество сравнений - %d\n",
               to_find, time,
               sizeof(FILE *), ec);
    }
    else
    {
        printf("Слово %s не найдено.\n",
               to_find);

        return VAL_ERROR;
    }

    fclose(f);

    return OK;
}