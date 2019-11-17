#ifndef __LISTSTACK_H__
#define __LISTSTACK_H__

typedef struct liststack
{
    int data;
    struct liststack *next;
} liststack_t;

liststack_t *create_node(int data);

int is_fulll(liststack_t *root, int limit);

int is_emptyl(liststack_t *root);

int pushl(liststack_t **root, int data, int limit);

int popl(liststack_t **root);

int free_stackl(liststack_t **root);

#endif