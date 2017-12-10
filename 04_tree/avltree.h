/* description of avl tree */
#ifndef __AVLTREE_H__
#define __AVLTREE_H__

typedef struct Tree Tree;

#define LEFT   1
#define RIGHT  2

struct Tree
{
    void *data;
    Tree *left;
    Tree *right;
    int height;
};

int tree_init(Tree **tree, void *data, int data_size);
int tree_create(Tree **tree, Tree *left, Tree *right, void *data, int data_size);
int tree_insert(Tree **tree, void *data, int data_size);
int tree_delete(Tree **tree, void *data, int data_size);
void tree_clear(Tree **tree);
int tree_find(Tree *tree, Tree **target, void *data, int data_size);
int tree_find_min(Tree *tree, Tree **target);
int tree_find_max(Tree *tree, Tree **target);

int tree_insert_nonrecur(Tree **tree, void *data, int data_size);

void tree_inorder_print_int(Tree *tree);
void tree_preorder_print_int(Tree *tree);
void tree_postorder_print_int(Tree *tree);

#endif
