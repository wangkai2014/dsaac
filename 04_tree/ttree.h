/* description of thread tree */
#ifndef __TTREE_H__
#define __TTREE_H__

typedef struct Tree Tree;

#define LEFT   1
#define RIGHT  2

#define MAX_TREE_DATA  100

struct Tree
{
    void *data;
    Tree *left;
    Tree *right;
    char lthread : 1;  /* 0: normal child; 1: thread child */
    char rthread : 1;  /* 0: normal child; 1: thread child */
};

int tree_init(Tree **tree, void *data, int data_size);
int tree_create(Tree **tree, Tree *left, Tree *right, void *data, int data_size);
int tree_insert(Tree **tree, void *data, int data_size);
int tree_delete(Tree **tree, void *data, int data_size);
void tree_clear(Tree **tree);
int tree_find(Tree *tree, Tree **target, void *data, int data_size);

int tree_init_by_int_arr(Tree **tree, int *arr, int num);

void tree_inorder_print_int(Tree *tree);
void tree_preorder_print_int(Tree *tree);
void tree_postorder_print_int(Tree *tree);
void tree_levelorder_print_int(Tree *tree);

#endif
