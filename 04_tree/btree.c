/* implementation of 2-3 tree */
#include "utils.h"
#include "btree.h"

int tree_create(Tree **in_tree, int data)
{
    Tree *tree = NULL;

    if (NULL == in_tree)
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    tree = (Tree *)malloc(sizeof(Tree));
    if (NULL == tree)
    {
        printf("%s(%d): failed to malloc memory for tree!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    tree->data = (int *)malloc(sizeof(int) * (ORDER + 1));
    if (NULL == tree->data)
    {
        printf("%s(%d): failed to malloc memory for tree's data!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    tree->child = (Tree **)malloc(sizeof(Tree *) * (ORDER + 1));
    if (NULL == tree->child)
    {
        printf("%s(%d): failed to malloc memory for tree's child!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    memset(tree->data, 0, sizeof(int) * (ORDER + 1));
    memset(tree->child, 0, sizeof(Tree *) * (ORDER + 1));

    tree->num = 1;
    tree->data[0] = data;
    *in_tree = tree;

    return SUCCESS;
}

static int btree_split(Tree **in_tree, int pos)
{}

static int btree_insert(Tree **in_tree, int data)
{
    int pos = 0;
    int result = SUCCESS;
    Tree *tree = *in_tree;

    if (NULL == tree->child[0])  /* leaf */
    {
        for (pos = tree->num; (pos > 0) && (tree->data[pos - 1] > data); pos--)
        {
            tree->data[pos] = tree->data[pos - 1];
        }

        tree->data[pos] = data;
        tree->num++;

        return SUCCESS;
    }

    /* find child tree that need to insert */
    for (pos = tree->num - 1; (pos > 0) && (tree->data[pos] > data); pos--);

    result = btree_insert(&tree->child[pos], data); 
    if ((SUCCESS == result) && (tree->child[pos]->num > ORDER))
    {
        result = btree_split(in_tree, pos);
    }

    return result;
}

int tree_insert(Tree **in_tree, int data)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    if (NULL == in_tree)
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    if (NULL == *in_tree)
    {
        result = tree_create(in_tree, data);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to create tree!\n", __FUNCTION__, __LINE__);
        }
    }
    else
    {
        result = btree_insert(in_tree, data);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to insert btree!\n", __FUNCTION__, __LINE__);
        }
    }

    return result;
}
