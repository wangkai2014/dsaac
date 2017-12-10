/* implementation of avl tree */
#include "utils.h"
#include "stack.h"
#include "avltree.h"

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
    tree->height = 0;

    *in_tree = tree;

    return SUCCESS;
}

static int tree_height(Tree *tree)
{
    if (NULL == tree)
    {
        return -1;
    }
    else
    {
        return tree->height;
    }
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
    tree->height = MAX(tree_height(left), tree_height(right)) + 1;

    *in_tree = tree;

    return SUCCESS;
}

static int cmp_data(void *a, void *b, int size)
{
    return ((*(int *)a > *(int *)b) ? 1 : ((*(int *)a == *(int *)b)? 0 : -1));
}

static int tree_is_balance(Tree *tree)
{
    return ((ABS(tree_height(tree->left), tree_height(tree->right)) > 1)? FALSE : TRUE);
}

static void tree_single_rotate_left(Tree **in_tree)
{
    Tree *tree = *in_tree;
    Tree *left = tree->left;

    tree->left = left->right;
    left->right = tree;
    tree->height = MAX(tree_height(tree->left), tree_height(tree->right)) + 1;

    *in_tree = left;
}

static void tree_single_rotate_right(Tree **in_tree)
{
    Tree *tree = *in_tree;
    Tree *right = tree->right;

    tree->right = right->left;
    right->left = tree;
    tree->height = MAX(tree_height(tree->left), tree_height(tree->right)) + 1;

    *in_tree = right;
}

static void tree_double_rotate_left(Tree **in_tree)
{
    Tree *tree = *in_tree;
    Tree *left = tree->left;
    Tree *right = left->right;

    left->right = right->left;
    right->left = left;
    left->height = MAX(tree_height(left->left), tree_height(left->right)) + 1;
    right->height = MAX(tree_height(right->left), tree_height(right->right)) + 1;

    left = right;
    tree->left = left->right;
    left->right = tree;
    tree->height = MAX(tree_height(tree->left), tree_height(tree->right)) + 1;

    *in_tree = left;
}

static void tree_double_rotate_right(Tree **in_tree)
{
    Tree *tree = *in_tree;
    Tree *right = tree->right;
    Tree *left = right->left;

    right->left = left->right;
    left->right = right;
    right->height = MAX(tree_height(right->left), tree_height(right->right)) + 1;
    left->height = MAX(tree_height(left->left), tree_height(left->right)) + 1;

    right = left;
    tree->right = right->left;
    right->left = tree;
    tree->height = MAX(tree_height(tree->left), tree_height(tree->right)) + 1;

    *in_tree = right;
}

static void tree_rebalance(Tree **in_tree)
{
    Tree *tree = *in_tree;

    if (tree_height(tree->right) > tree_height(tree->left))
    {
        if (tree_height(tree->right->right) > tree_height(tree->right->left))
        {
            tree_single_rotate_right(in_tree);
        }
        else
        {
            tree_double_rotate_right(in_tree);
        }
    }
    else
    {
        if (tree_height(tree->left->left) > tree_height(tree->left->right))
        {
            tree_single_rotate_left(in_tree);
        }
        else
        {
            tree_double_rotate_left(in_tree);
        }
    }
}

static int avl_tree_insert(Tree **in_tree, Tree *node, int data_size)
{
    Tree *tree = *in_tree;
    Tree **child = NULL;
    int result = SUCCESS;
    int cmp_result;

    cmp_result = cmp_data(tree->data, node->data, data_size);
    if (cmp_result == 0)
    {
        printf("%s(%d): data has existed!\n", __FUNCTION__, __LINE__);
        return DUPLICATED;
    }

    child = (cmp_result < 0) ? &tree->right : &tree->left;

    if (NULL == *child)
    {
        *child = node;
    }
    else
    {
        result = avl_tree_insert(child, node, data_size);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to insert avl tree!\n", __FUNCTION__, __LINE__);
            return result;
        }
    }

    tree->height = MAX(tree_height(tree->left), tree_height(tree->right)) + 1;

    if (!tree_is_balance(tree))
    {
        tree_rebalance(in_tree);
    }

    return SUCCESS;
}

int tree_insert(Tree **tree, void *data, int data_size)
{
    int result;
    Tree *node = NULL;

    if ((NULL == tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    } 

    result = tree_init(&node, data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
        return result;
    }

    if (NULL == *tree)  /* empty tree */
    {
        *tree = node;
        return SUCCESS;
    }

    result = avl_tree_insert(tree, node, data_size);
    if (SUCCESS != result)
    {
        tree_clear(&node);

        printf("%s(%d): failed to insert avl tree!\n", __FUNCTION__, __LINE__);
    }

    return result;
}

static int avl_tree_rebalance(Stack *stck)
{
    int result;
    Tree **tree = NULL;

    while (!stack_is_empty(stck))
    {
        result = stack_pop(stck, &tree, sizeof(tree));
        if (SUCCESS != result)
        {
            printf("%s(%d): err %d: failed to pop stack!\n", __FUNCTION__, __LINE__, result);
            return result;
        }

        if (!tree_is_balance(*tree))
        {
            tree_rebalance(tree);
        }

        (*tree)->height = MAX(tree_height((*tree)->left), tree_height((*tree)->right)) + 1;
    }

    return SUCCESS;
}

static int avl_tree_insert_nonrecur(Tree **in_tree, Tree *node, int data_size, Stack *stck)
{
    Tree **tree = in_tree;
    int result = SUCCESS;
    int cmp_result;

    while (NULL != *tree)
    {
        cmp_result = cmp_data((*tree)->data, node->data, data_size);
        if (cmp_result == 0)
        {
            printf("%s(%d): data has existed!\n", __FUNCTION__, __LINE__);
            return DUPLICATED;
        }

        result = stack_push(stck, &tree, sizeof(tree));
        if (SUCCESS != result)
        {
            printf("%s(%d): err %d: failed to push stack!\n", __FUNCTION__, __LINE__, result);
            return result;
        }

        tree = (cmp_result < 0) ? &(*tree)->right : &(*tree)->left;
    }

    *tree = node;

    return SUCCESS;
}

int tree_insert_nonrecur(Tree **tree, void *data, int data_size)
{
    int result;
    Tree *node = NULL;
    Stack *stck = NULL;

    if ((NULL == tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    } 

    result = tree_init(&node, data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
        return result;
    }

    if (NULL == *tree)  /* empty tree */
    {
        *tree = node;
        return SUCCESS;
    }

    result = stack_init(&stck, sizeof(Tree **));
    if (SUCCESS != result)
    {
        printf("%s(%d): err[%d]: failed to init stack!\n", __FUNCTION__, __LINE__, result);
        return result;
    }

    result = avl_tree_insert_nonrecur(tree, node, data_size, stck);
    if (SUCCESS != result)
    {
        printf("%s(%d): err[%d]: failed to insert avl tree!\n", __FUNCTION__, __LINE__, result);
        tree_clear(&node);
        return result;
    }

    result = avl_tree_rebalance(stck);
    if (SUCCESS != result)
    {
        printf("%s(%d): err[%d]: failed to rebalance avl tree!\n", __FUNCTION__, __LINE__, result);
        tree_clear(&node);
    }

    stack_clear(&stck);

    return SUCCESS;
}

static void tree_refresh_left_height(Tree *tree)
{
    if (NULL != tree->left)
    {
        tree_refresh_left_height(tree->left);
    }

    tree->height = MAX(tree_height(tree->left), tree_height(tree->right)) + 1;
}

static int tree_delete_min(Tree **tree, Tree **target)
{
    int result = SUCCESS;
    Tree **link = NULL;
    Tree *min = NULL;
    
    if ((NULL == tree) || (NULL == *tree) || (NULL == target))
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    link = tree;
    min = *tree;
    while (NULL != min->left)
    {
        link = &min->left;
        min = min->left;
    }

    *link = min->right;
    *target = min;

    if (NULL != *tree)
    {
        tree_refresh_left_height(*tree);
    }
    
    return SUCCESS;
}

static int avl_tree_delete_cur(Tree **in_tree)
{
    int result = SUCCESS;
    Tree *tree = *in_tree;
    Tree *min = NULL;

    if (NULL == tree->left)
    {
        *in_tree = tree->right;
    }
    else if (NULL == tree->right)
    {
        *in_tree = tree->left;
    }
    else
    {
        result = tree_delete_min(&tree->right, &min);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to delete min!\n", __FUNCTION__, __LINE__);
            return result;
        }

        min->left = tree->left;
        min->right = tree->right;
        min->height = MAX(tree_height(min->left), tree_height(min->right)) + 1;
        *in_tree = min;
    }

    free(tree->data);
    free(tree);

    return SUCCESS;
}

static int avl_tree_delete(Tree **in_tree, void *data, int data_size)
{
    int result = SUCCESS;
    int cmp_result = 0;
    Tree *tree = *in_tree;

    if (NULL == tree)
    {
        printf("%s(%d): cannot find the node to be deleted!\n", __FUNCTION__, __LINE__);
        return NOT_FOUND;
    }

    cmp_result = cmp_data(tree->data, data, data_size);

    if (cmp_result == 0)  /* cur node is to be deleted */
    {
        result = avl_tree_delete_cur(in_tree);
    }
    else if (cmp_result < 0)
    {
        result = avl_tree_delete(&tree->right, data, data_size);
    }
    else
    {
        result = avl_tree_delete(&tree->left, data, data_size);
    }

    tree->height = MAX(tree_height(tree->left), tree_height(tree->right)) + 1;

    if (!tree_is_balance(tree))
    {
        tree_rebalance(in_tree);
    }

    return result;
}

int tree_delete(Tree **tree, void *data, int data_size)
{
    int result = SUCCESS;

    if ((NULL == tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    } 

    result = avl_tree_delete(tree, data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to delete avl tree!\n", __FUNCTION__, __LINE__);
    }

    return result;
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

int tree_find(Tree *tree, Tree **target, void *data, int data_size)
{
    int result = 0;
    Tree *cur = tree;

    if ((NULL == tree) || (NULL == target) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): null pointer! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    }

    while ((NULL != cur) && (0 != result))
    {
        result = cmp_data(data, cur->data, data_size);

        cur = (result < 0) ? cur->left : cur->right;
    }

    *target = cur;

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

    printf("%d(%d) ", *(int *)tree->data, tree->height);

    tree_inorder_print_int(tree->right);
}

void tree_preorder_print_int(Tree *tree)
{
    if (NULL == tree)
    {
        return;
    }

    printf("%d(%d) ", *(int *)tree->data, tree->height);

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

    printf("%d(%d) ", *(int *)tree->data, tree->height);
}
