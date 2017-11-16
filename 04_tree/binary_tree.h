#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef struct Tree Tree;

struct Tree
{
    void *data;
    Tree *left;
    Tree *right;
};

int tree_init(Tree **tree, int data_size);
int tree_create(Tree **tree, Tree *left, Tree *right, void *data, int data_size);
int tree_insert(Tree *tree, void *data);
int tree_delete(Tree *tree);
int tree_clear(Tree **tree);

#endif
