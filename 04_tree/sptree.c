/* implementation of splay tree */
#include "utils.h"
#include "sptree.h"

int tree_init(Tree **in_tree, void *data, int data_size)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    if ((NULL == in_tree) || (NULL == data) || (data_size <= 0))
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

    memcpy(tree->data, data, data_size);

    tree->left = NULL;
    tree->right = NULL;

    *in_tree = tree;

    return SUCCESS;
}

int tree_create(Tree **in_tree, Tree *left, Tree *right, void *data, int data_size)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    if ((NULL == in_tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invaild input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
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

    memcpy(tree->data, data, data_size);

    tree->left = left;
    tree->right = right;

    *in_tree = tree;

    return SUCCESS;
}

static int cmp_data(void *a, void *b, int size)
{
    return ((*(int *)a > *(int *)b) ? 1 : ((*(int *)a == *(int *)b)? 0 : -1));
}

int tree_insert(Tree **tree, void *data, int data_size)
{
    int result;
    Tree **link = NULL;
    Tree *cur = NULL;

    if ((NULL == tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    } 

    link = tree;
    cur = *tree;

    while (NULL != cur)
    {
        result = cmp_data(data, cur->data, data_size);
        if (0 == result)
        {
            printf("%s(%d): the node has existed!\n", __FUNCTION__, __LINE__);
            return DUPLICATED;
        }

        link = (result < 0) ? &cur->left : &cur->right;
        cur = (result < 0) ? cur->left : cur->right;
    }

    result = tree_init(link, data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
        return result;
    }

    return SUCCESS;
}

int tree_delete(Tree **tree, void *data, int data_size)
{
    int result = SUCCESS;
    Tree *cur = NULL;

    if ((NULL == tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    } 

    result = tree_find(tree, data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to find the data!\n", __FUNCTION__, __LINE__);
        return result;
    }

    cur = *tree;

    if (NULL == cur->left)
    {
        *tree = cur->right;
        free(cur->data);
        free(cur);
        return SUCCESS;
    }

    cur = cur->left;

    /* find the lastest node in the left child */
    while (NULL != cur->right)
    {
        cur = cur->right;
    }

    result = tree_find(&(*tree)->left, cur->data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to find the lastest left child!\n", __FUNCTION__, __LINE__);
        return result;
    }

    cur = *tree;
    cur->left->right = cur->right;
    *tree = cur->left;
    free(cur->data);
    free(cur);

    return SUCCESS;
}

void tree_clear(Tree **tree)
{
    if (NULL == *tree)
    {
        return;
    }

    tree_clear(&(*tree)->left);
    tree_clear(&(*tree)->right);

    free((*tree)->data);
    *tree = NULL;
}

static void tree_single_rotate_left(Tree **tree)
{
    Tree *left = (*tree)->left;

    (*tree)->left = left->right;
    left->right = *tree; 
    *tree = left;
}

static void tree_single_rotate_right(Tree **tree)
{
    Tree *right = (*tree)->right;

    (*tree)->right = right->left;
    right->left = *tree;
    *tree = right;
}

static void splay_tree_rotate(Tree **in_tree, void *data, int data_size)
{
    Tree *tree = *in_tree;

    if (NULL != tree->left)
    {
        if ((NULL != tree->left->left) && (0 == cmp_data(tree->left->left->data, data, data_size)))
        {
            tree_single_rotate_left(in_tree);
            tree_single_rotate_left(in_tree);
        }
        else if ((NULL != tree->left->right) && (0 == cmp_data(tree->left->right->data, data, data_size)))
        {
            tree_single_rotate_right(&tree->left);
            tree_single_rotate_left(in_tree);
        }
    }

    if (NULL != tree->right)
    {
        if ((NULL != tree->right->right) && (0 == cmp_data(tree->right->right->data, data, data_size)))
        {
            tree_single_rotate_right(in_tree);
            tree_single_rotate_right(in_tree);
        }
        else if ((NULL != tree->right->left) && (0 == cmp_data(tree->right->left->data, data, data_size)))
        {
            tree_single_rotate_left(&tree->right);
            tree_single_rotate_right(in_tree);
        }
    }
}

static int splay_tree_find(Tree **tree, void *data, int data_size)
{
    int result = SUCCESS;

    if (NULL == *tree)
    {
        return NOT_FOUND;
    }

    splay_tree_rotate(tree, data, data_size);

    result = cmp_data((*tree)->data, data, data_size);

    if (result == 0)
    {
        return SUCCESS;
    }
    else if (result < 0)
    {
        result = splay_tree_find(&(*tree)->right, data, data_size);
    }
    else
    {
        result = splay_tree_find(&(*tree)->left, data, data_size);
    }

    if (SUCCESS == result)
    {
        splay_tree_rotate(tree, data, data_size);
    }

    return result;
}

int tree_find(Tree **tree, void *data, int data_size)
{
    int result = 0;

    if ((NULL == tree) || (NULL == *tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): null pointer! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    }

    result = splay_tree_find(tree, data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to find the target in splay tree!\n", __FUNCTION__, __LINE__);
        return result;
    }

    result = cmp_data((*tree)->data, data, data_size);
    if (result > 0)
    {
        tree_single_rotate_left(tree);
    }
    else if (result < 0)
    {
        tree_single_rotate_right(tree);
    }

    return SUCCESS;
}

int tree_find_min(Tree *tree, Tree **target)
{
    Tree *cur = tree;

    if ((NULL == tree) || (NULL == target)) 
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    while (NULL != cur->left)
    {
        cur = cur->left;
    }

    *target = cur;

    return SUCCESS;
}

int tree_find_max(Tree *tree, Tree **target)
{
    Tree *cur = tree;

    if ((NULL == tree) || (NULL == target)) 
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    while (NULL != cur->right)
    {
        cur = cur->right;
    }

    *target = cur;

    return SUCCESS;
}

void tree_inorder_print_int(Tree *tree)
{
    if (NULL == tree)
    {
        return;
    }

    tree_inorder_print_int(tree->left);

    printf("%d ", *(int *)tree->data);

    tree_inorder_print_int(tree->right);
}

void tree_preorder_print_int(Tree *tree)
{
    if (NULL == tree)
    {
        return;
    }

    printf("%d ", *(int *)tree->data);

    tree_preorder_print_int(tree->left);

    tree_preorder_print_int(tree->right);
}

void tree_postorder_print_int(Tree *tree)
{
    if (NULL == tree)
    {
        return;
    }

    tree_postorder_print_int(tree->left);

    tree_postorder_print_int(tree->right);

    printf("%d ", *(int *)tree->data);
}
