/* description of tree stored with child/sibling link */
#ifndef __CSTREE_H__
#define __CSTREE_H__

typedef struct Tree Tree;

#define LEFT   1
#define RIGHT  2

#define MAX_TREE_DATA  100

struct Tree
{
    void *data;
    Tree *sibl;
    Tree *child;
};

int tree_init(Tree **tree, void *data, int data_size);
int tree_create(Tree **tree, Tree *sibl, Tree *child, void *data, int data_size);
int tree_insert(Tree **tree, void *data, int data_size);
int tree_delete(Tree **tree, void *data, int data_size);
void tree_clear(Tree **tree);
int tree_find(Tree *tree, Tree **target, void *data, int data_size);

int tree_init_by_int_arr(Tree **tree, int *arr, int num);

void tree_preorder_print_int(Tree *tree);
void tree_inorder_print_int(Tree *tree);
void tree_postorder_print_int(Tree *tree);
void tree_levelorder_print_int(Tree *tree);

#endif
