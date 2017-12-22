/* description of binary search tree */
#ifndef __BSTREE_H__
#define __BSTREE_H__

typedef struct Tree Tree;
typedef struct Position Position;

#define LEFT   1
#define RIGHT  2

#define MAX_TREE_DATA  100

struct Position
{
    int x;
    int y;
};

struct Tree
{
    void *data;
    Tree *left;
    Tree *right;
    Position *pos;
};

int tree_init(Tree **tree, void *data, int data_size);
int tree_create(Tree **tree, Tree *left, Tree *right, void *data, int data_size);
int tree_insert(Tree **tree, void *data, int data_size);
int tree_delete(Tree **tree, void *data, int data_size);
void tree_clear(Tree **tree);
int tree_height(Tree *tree);
int tree_internal_path_len(Tree *tree);
int tree_find(Tree *tree, Tree **target, void *data, int data_size);
int tree_find_min(Tree *tree, Tree **target);
int tree_find_max(Tree *tree, Tree **target);
void tree_set_position(Tree *tree);
int tree_random_create(Tree **tree, int num);

int tree_init_by_int_arr(Tree **tree, int *arr, int num);

void tree_inorder_print_int(Tree *tree);
void tree_preorder_print_int(Tree *tree);
void tree_postorder_print_int(Tree *tree);

#endif
