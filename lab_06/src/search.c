#include "include/search.h"

char **fill_words(FILE *f)
{
    rewind(f);

    unsigned long flen = file_len(f);

    int ind = 0;
    char buffer[STR_SIZE];
    char **words = (char **)malloc(sizeof(char *) * flen);
    for (int i = 0; i < flen; ++i)
    {
        words[i] = (char *)malloc(sizeof(char) * STR_SIZE);
    }

    while (fgets(buffer, STR_SIZE, f) != NULL)
    {
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        strcpy(words[ind], buffer);
        ind++;
    }

    rewind(f);

    return words;
}

void free_words(char **words, unsigned long flen)
{
    for (int i = 0; i < flen; ++i)
    {
        free(words[i]);
    }

    free(words);
}

int search_tree(char *to_find, tree_node root)
{
    int i = 0;
    tree_node *p = &root;

    while (p != NULL)
    {
        i++;
        if (strcmp(p->val, to_find) == 0)
            return i;

        if (strcmp(p->val, to_find) > 0)
            p = p->right;
        else
            p = p->left;
    }

    return NOT_FOUND;
}

double search_tree_av(tree_node root, char **words, unsigned long flen)
{
    uint64_t time = tick();
    for (int i = 0; i < flen; ++i)
    {
        search_tree(words[i], root);
    }
    time = tick() - time;

    return (double)time / flen;
}

int search_hashtable(char *to_find, list_t *hash_list, int n, int (*hash)(char *, int))
{
    int ec = deepcmp(to_find, hash_list[hash(to_find, n)]);
    if (ec > 0)
        return ec;

    return NOT_FOUND;
}

double search_hashtable_av(list_t *hash_list, int n, int (*hash)(char *, int),
                           char **words, unsigned long flen)
{
    uint64_t time = tick();
    for (int i = 0; i < flen; ++i)
    {
        search_hashtable(words[i], hash_list, n, hash);
    }
    time = tick() - time;

    return (double)time / flen;
}

int search_file(char *to_find, FILE *f)
{
    rewind(f);

    int i = 0;
    char buffer[STR_SIZE];

    while (fgets(buffer, STR_SIZE, f) != NULL)
    {
        i++;
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        if (strcmp(to_find, buffer) == 0)
        {
            return i;
        }
    }

    rewind(f);

    return NOT_FOUND;
}

double search_file_av(FILE *f, char **words, unsigned long flen)
{
    uint64_t time = tick();
    for (int i = 0; i < flen; ++i)
    {
        search_file(words[i], f);
    }
    time = tick() - time;

    return (double)time / flen;
}