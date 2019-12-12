#include "include/tree_utils.h"

tree_node *create_node(char *val)
{
    tree_node *node = malloc(sizeof(tree_node));

    node->val = malloc(sizeof(char *) * (strlen(val) + 1));
    strcpy(node->val, val);

    node->left = NULL;
    node->right = NULL;

    return node;
}

tree_node *insert(tree_node *node, char *val)
{
    if (node == NULL)
    {
        return create_node(val);
    }

    if (strcmp(val, node->val) > 0)
    {
        node->left = insert(node->left, val);
    }
    else
    {
        if (strcmp(val, node->val) < 0)
        {
            node->right = insert(node->right, val);
        }
    }

    return node;
}

void fill_tree(tree_node **root, FILE *f)
{
    char buffer[STR_SIZE];

    fgets(buffer, STR_SIZE, f);
    if (buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }

    *root = insert(*root, buffer);

    while (fgets(buffer, STR_SIZE, f) != NULL)
    {
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        insert(*root, buffer);
    }

    rewind(f);
}

void print_tree(tree_node *root, int space)
{
    if (root == NULL)
    {
        return;
    }

    space += SPACING;

    print_tree(root->right, space);

    printf("\n");
    for (int i = SPACING; i < space; i++)
    {
        printf(" ");
    }
    printf("%s\n", root->val);

    print_tree(root->left, space);
}

void push_back(dynarr *arr, tree_node *to_add)
{
    arr->size++;
    if (arr->size >= arr->mem_size)
    {
        arr->mem_size *= 2;
        arr->arr = realloc(arr->arr, arr->mem_size * sizeof(tree_node *)); // криво
    }

    for (int i = arr->size; i > 0; i--)
    {
        arr->arr[i] = arr->arr[i - 1];
    }

    arr->arr[0] = to_add;
}

void store_nodes(tree_node *root, dynarr *arr)
{
    if (root == NULL)
    {
        return;
    }

    store_nodes(root->left, arr);
    push_back(arr, root);
    store_nodes(root->right, arr);
}

tree_node *build_tree(dynarr *arr, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    int mid = (start + end) / 2;
    tree_node *root = arr->arr[mid];

    root->right = build_tree(arr, start, mid - 1);
    root->left = build_tree(arr, mid + 1, end);

    return root;
}

tree_node *balance_tree(tree_node *root, int *unique)
{
    dynarr arr;
    arr.mem_size = 8;
    arr.size = 0;
    arr.arr = malloc(sizeof(tree_node *) * arr.mem_size); // криво
    store_nodes(root, &arr);

    int n = arr.size;
    *unique = n;

    tree_node *r = build_tree(&arr, 0, n - 1);

    free(arr.arr);

    return r;
}

void free_tree(tree_node *node)
{
    if (node == NULL)
    {
        return;
    }

    free_tree(node->left);
    free_tree(node->right);

    free(node);
}