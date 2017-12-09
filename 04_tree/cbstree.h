/* description of binary search tree using cursor */
#ifndef __CBSTREE_H__
#define __CBSTREE_H__

#define INVALID_TREE  -1

typedef int Tree;

Tree tree_init(int data);
int tree_insert(Tree root, int data);
Tree tree_delete(Tree root, int data);
Tree tree_find(Tree root, int data);
void tree_clear(Tree root);

void tree_preorder_print(Tree root);
void tree_inorder_print(Tree root);
void tree_postorder_print(Tree root);

void cursor_init();

#endif
