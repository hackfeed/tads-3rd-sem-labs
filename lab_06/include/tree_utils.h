#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/macro.h"
#include "include/rc.h"

typedef struct tree_node
{
    char *val;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

typedef struct
{
    tree_node **arr;
    int size;
    int mem_size;
} dynarr;

tree_node *create_node(char *val);

tree_node *insert(tree_node *node, char *val);

void fill_tree(tree_node **root, FILE *f);

void print_tree(tree_node *root, int space);

void push_back(dynarr *arr, tree_node *to_add);

void store_nodes(tree_node *root, dynarr *arr);

tree_node *build_tree(dynarr *arr, int start, int end);

tree_node *balance_tree(tree_node *root, int *unique);

void free_tree(tree_node *node);

#endif