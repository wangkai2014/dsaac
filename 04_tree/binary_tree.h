#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef struct Tree Tree;
typedef void (*Visit)(Tree *, char *, int *);

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

void tree_preorder_visit(Tree *tree, Visit visit, char *str, int *start);
void tree_inorder_visit(Tree *tree, Visit visit, char *str, int *start);
void tree_postorder_visit(Tree *tree, Visit visit, char *str, int *start);

#endif
