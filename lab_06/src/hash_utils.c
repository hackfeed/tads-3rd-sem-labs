#include "include/hash_utils.h"

int is_prime(unsigned int num)
{
    if (num <= 1)
        return 0;
    if (num % 2 == 0 && num > 2)
        return 0;
    for (int i = 3; i < floor(sqrt(num)); i += 2)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

unsigned int next_prime(int n)
{
    unsigned int prime = n + 1;
    while (!is_prime(prime))
    {
        prime++;
    }

    return prime;
}

int safe_hash(char *s, int n)
{
    unsigned long pow = 1, code_pow = 0;
    int pow_mult = 26;

    do
    {
        code_pow += *s * pow;
        pow *= pow_mult;
    } while (*(s++));

    return code_pow % n;
}

int unsafe_hash(char *s, const int n)
{
    int hash = 0;

    for (; *s; hash += *(s++))
        ;

    return hash % n;
}

int file_len(FILE *f)
{
    rewind(f);

    int lines = 0;
    char buffer[STR_SIZE];

    while (fgets(buffer, STR_SIZE, f) != NULL)
    {
        lines++;
    }

    rewind(f);

    return lines;
}

int fbytes(FILE *f)
{
    rewind(f);
    fseek(f, 0, SEEK_END);
    unsigned size = ftell(f);
    rewind(f);

    return size;
}

int build_hash_table(list_t **arr, int size, FILE *f, int (*hash)(char *, int))
{
    char buffer[STR_SIZE];
    int max_collisions = 0;

    while (fgets(buffer, STR_SIZE, f) != NULL)
    {
        int cur_collisions = 0;
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        if (deepcmp(buffer, (*arr)[hash(buffer, size)]) == 0)
        {
            cur_collisions = linsert(&(*arr)[hash(buffer, size)], buffer);
        }

        if (cur_collisions > max_collisions)
        {
            max_collisions = cur_collisions;
        }
    }

    rewind(f);

    return max_collisions;
}

void print_hash_table(list_t *arr, int size)
{
    printf(ANSI_COLOR_GREEN
           "\n------------------------------------------\n"
           "  ХЕШ | СООТВЕТСТВУЮЩИЕ ДАННЫЕ\n"
           "------------------------------------------\n" ANSI_COLOR_RESET);
    list_t *entry;

    int f = 0;

    for (int i = 0; i < size; i++)
    {
        f = 0;

        entry = &arr[i];
        if (entry->value != NULL)
        {
            printf("%5d | ", i);
            f = 1;
        }
        while (entry != NULL)
        {
            if (entry->value != NULL)
                printf("\"%s\" ", entry->value);
            entry = entry->next;
        }
        if (f)
            printf("\n------------------------------------------\n");
    }
}
