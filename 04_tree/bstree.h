/* description of binary search tree */
#ifndef __BSTREE_H__
#define __BSTREE_H__

typedef struct Tree Tree;

#define LEFT   1
#define RIGHT  2

struct Tree
{
    void *data;
    Tree *left;
    Tree *right;
};

int tree_init(Tree **tree, void *data, int data_size);
int tree_create(Tree **tree, Tree *left, Tree *right, void *data, int data_size);
int tree_insert(Tree **tree, void *data, int data_size);
int tree_delete(Tree **tree, void *data, int data_size);
void tree_clear(Tree **tree);
int tree_find(Tree *tree, Tree **target, void *data, int data_size);
int tree_find_parent(Tree *tree, Tree **parent, int *dir, void *data, int data_size);
int tree_find_min(Tree *tree, Tree **target);
int tree_find_max(Tree *tree, Tree **target);

#endif
