#include <stdio.h>

#include "include/rc.h"
#include "include/arrstack.h"
#include "include/liststack.h"

int main()
{
    int limit = 0xFFFFFFFF;
    liststack_t *root = NULL;
    pushl(&root, 10, limit);
    pushl(&root, 222, limit);
    int el = popl(&root);
    free_stackl(&root);

    printf("%d cur stack el\n", el);

    return OK;
}