#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stdio.h>

#include "include/rc.h"
#include "include/macro.h"

#include "include/tree_utils.h"
#include "include/list_utils.h"

int search_tree(char *to_find, tree_node root);

int search_hashtable(char *to_find, list_t *hash_list, int n, int (*hash)(char *, int));

int search_file(char *to_find, FILE *f);

#endif