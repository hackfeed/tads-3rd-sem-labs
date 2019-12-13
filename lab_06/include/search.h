#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stdio.h>

#include "include/rc.h"
#include "include/macro.h"

#include "include/tree_utils.h"
#include "include/list_utils.h"
#include "include/timer.h"

char **fill_words(FILE *f);

void free_words(char **words, unsigned long flen);

int search_tree(char *to_find, tree_node root);

double search_tree_av(tree_node root, char **words, unsigned long flen);

int search_hashtable(char *to_find, list_t *hash_list, int n, int (*hash)(char *, int));

double search_hashtable_av(list_t *hash_list, int n, int (*hash)(char *, int), char **words, unsigned long flen);

int search_file(char *to_find, FILE *f);

double search_file_av(FILE *f, char **words, unsigned long flen);

#endif