#include "include/search.h"

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

int search_hashtable(char *to_find, list_t *hash_list, int n, int (*hash)(char *, int))
{
    int ec = deepcmp(to_find, hash_list[hash(to_find, n)]);
    if (ec > 0)
        return ec;

    return NOT_FOUND;
}

int search_file(char *to_find, FILE *f)
{
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

    return NOT_FOUND;
}