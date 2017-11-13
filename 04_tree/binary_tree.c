#include "utils.h"
#include "binary_tree.h"

int tree_init(Tree **in_tree, int data_size)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    if ((NULL == in_tree) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    }

    tree = (Tree *)malloc(sizeof(Tree));
    if (NULL == tree)
    {
        printf("%s(%d): failed to malloc memory!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    tree->data = malloc(data_size);
    if (NULL == tree->data)
    {
        printf("%s(%d): failed to malloc memory!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    memset(tree->data, 0, data_size);

    tree->left = NULL;
    tree->right = NULL;

    *in_tree = tree;

    return SUCCESS;
}

int tree_create(Tree **in_tree, Tree *left, Tree *right, void *data, int data_size)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    tree = (Tree *)malloc(sizeof(Tree));
    if (NULL == tree)
    {
        printf("%s(%d): failed to malloc memory!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    tree->data = malloc(data_size);
    if (NULL == tree->data)
    {
        printf("%s(%d): failed to malloc memory!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    memcpy(tree->data, data, data_size);

    tree->left = left;
    tree->right = right;

    *in_tree = tree;

    return SUCCESS;
}

int tree_insert(Tree *tree, void *data)
{
    int result = SUCCESS;

    return result;
}

int tree_delete(Tree *tree)
{
    int result = SUCCESS;

    return result;
}

int tree_clear(Tree **tree)
{
    int result = SUCCESS;

    return result;
}

void tree_preorder_visit(Tree *tree, Visit visit, char *str, int *start)
{
    if ((NULL == tree) || (NULL == visit))
    {
        return;
    }

    (*visit)(tree, str, start);
    tree_preorder_visit(tree->left, visit, str, start);
    tree_preorder_visit(tree->right, visit, str, start);
}

void tree_inorder_visit(Tree *tree, Visit visit, char *str, int *start)
{
    if ((NULL == tree) || (NULL == visit))
    {
        return;
    }

    tree_inorder_visit(tree->left, visit, str, start);
    (*visit)(tree, str, start);
    tree_inorder_visit(tree->right, visit, str, start);
}

void tree_postorder_visit(Tree *tree, Visit visit, char *str, int *start)
{
    if ((NULL == tree) || (NULL == visit))
    {
        return;
    }

    tree_postorder_visit(tree->left, visit, str, start);
    tree_postorder_visit(tree->right, visit, str, start);
    (*visit)(tree, str, start);
}