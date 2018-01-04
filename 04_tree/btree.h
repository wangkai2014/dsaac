/* description of 2-3 tree */
#ifndef __BTREE_H__
#define __BTREE_H__

#define ORDER  3

typedef struct Tree Tree;
typedef int Data; 

struct Tree
{
    /* we set the size of array is one more than order 
     * for the convenience of insertion */
    Tree *parent;
    Data *data[ORDER + 1];
    Tree *child[ORDER + 1];
};

int tree_init(Tree **tree);
int tree_insert(Tree **tree, Data *data);
int tree_delete(Tree **tree, Data *data);
void tree_clear(Tree **tree);
int tree_find(Tree *tree, Tree **target, Data *data);

void tree_levelorder_print_int(Tree *tree);

#endif
