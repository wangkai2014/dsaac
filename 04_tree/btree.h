/* description of 2-3 tree */
#ifndef __BTREE_H__
#define __BTREE_H__

#define ORDER  3

typedef struct Tree Tree;

struct Tree
{
    int num;     /* number of child nodes */
    int *data;
    Tree **child;
};

int tree_create(Tree **tree, int data);
int tree_insert(Tree **tree, int data);
int tree_delete(Tree **tree, int data);
void tree_clear(Tree **tree);
int tree_find(Tree *tree, Tree **target, int data);

void tree_inorder_print_int(Tree *tree);
void tree_preorder_print_int(Tree *tree);
void tree_postorder_print_int(Tree *tree);

#endif
