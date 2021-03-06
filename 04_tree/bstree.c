/* implementation of binary search tree */
#include "utils.h"
#include "queue.h"
#include "bstree.h"

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

    tree->pos = malloc(sizeof(Position));
    if (NULL == tree->pos)
    {
        printf("%s(%d): failed to malloc memory!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    memset(tree->pos, 0, sizeof(Position));

    tree->left = NULL;
    tree->right = NULL;
    tree->node_num = 1;

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
            printf("%s(%d): the node[%d] has existed!\n", __FUNCTION__, __LINE__, *(int*)data);
            return DUPLICATED;
        }

        cur->node_num++;
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
    
    return SUCCESS;
}

/**
 * if root->data == data, *link = &root;
 * if cur->data == data, and cur is parent's left child, *link = &parent->left
 * if cur->data == data, and cur is parent's right child, *link = &parent->right
 */
int tree_find_parent_link(Tree **tree, Tree ***link, void *data, int data_size)
{
    int result = 0;
    Tree *cur = NULL;

    if ((NULL == tree) || (NULL == link) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    }

    *link = tree;
    cur = *tree;

    while (NULL != cur)
    {
        result = cmp_data(data, cur->data, data_size);
        if (0 == result)
        {
            return SUCCESS;
        }
        
        *link = (result < 0) ? &cur->left : &cur->right;
        cur = (result < 0) ? cur->left : cur->right;
    }

    return NOT_FOUND;
}

int tree_delete(Tree **tree, void *data, int data_size)
{
    int result = SUCCESS;
    Tree **link = NULL;
    Tree *cur = NULL;
    Tree *min = NULL;

    if ((NULL == tree) || (NULL == data) || (data_size <= 0))
    {
        printf("%s(%d): invalid input! data_size=%d.\n", __FUNCTION__, __LINE__, data_size);
        return INVALID_INPUT;
    } 

    result = tree_find_parent_link(tree, &link, data, data_size);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to find parent link!\n", __FUNCTION__, __LINE__);
        return result;
    }

    cur = *link;

    if (NULL == cur->left)
    {
        *link = cur->right;
    }
    else if (NULL == cur->right)
    {
        *link = cur->left;
    }
    else
    {
        result = tree_delete_min(&cur->right, &min);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to delete min!\n", __FUNCTION__, __LINE__);
            return result;
        }

        min->left = cur->left;
        min->right = cur->right;
        *link = min;
    }

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
    free(*tree);
    *tree = NULL;
}

int tree_height(Tree *tree)
{
    if (NULL == tree)
    {
        return 0;
    }

    return (MAX(tree_height(tree->left), tree_height(tree->right)) + 1);
}

static int tree_ipl(Tree *tree, int depth)
{
    if (NULL == tree)
    {
        return 0;
    }

    return (depth + tree_ipl(tree->left, depth + 1) + tree_ipl(tree->right, depth + 1));
}

int tree_internal_path_len(Tree *tree)
{
    return tree_ipl(tree, 0);
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

    printf("%d(%d) ", *(int *)tree->data, tree->node_num);

    tree_inorder_print_int(tree->right);
}

void tree_preorder_print_int(Tree *tree)
{
    if (NULL == tree)
    {
        return;
    }

    printf("%d(%d) ", *(int *)tree->data, tree->node_num);

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

    printf("%d(%d) ", *(int *)tree->data, tree->node_num);
}

void tree_levelorder_print_int(Tree *in_tree)
{
    int result;
    Queue *queue = NULL;
    Tree *tree = in_tree;

    if (NULL == tree)
    {
        return;
    }

    result = queue_init(&queue, sizeof(Tree *));
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to init queue!\n", __FUNCTION__, __LINE__);
        return;
    }

    result = queue_enqueue(queue, &tree, sizeof(Tree *));
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to enqueue tree.\n", __FUNCTION__, __LINE__);
        return;
    }

    while (!queue_is_empty(queue))
    {
        result = queue_dequeue(queue, &tree, sizeof(Tree *));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to dequeue tree.\n", __FUNCTION__, __LINE__);
            queue_clear(&queue);
            return;
        }

        printf("%d(%d) ", *(int *)tree->data, tree->node_num);

        if (NULL != tree->left)
        {
            result = queue_enqueue(queue, &tree->left, sizeof(Tree *));
            if (SUCCESS != result)
            {
                printf("%s(%d): failed to enqueue tree.\n", __FUNCTION__, __LINE__);
                queue_clear(&queue);
                return;
            }
        }

        if (NULL != tree->right)
        {
            result = queue_enqueue(queue, &tree->right, sizeof(Tree *));
            if (SUCCESS != result)
            {
                printf("%s(%d): failed to enqueue tree.\n", __FUNCTION__, __LINE__);
                queue_clear(&queue);
                return;
            }
        }
    }

    queue_clear(&queue);
}

int tree_init_by_int_arr(Tree **tree, int *arr, int num)
{
    int result;
    int pos;

    if ((NULL == tree) || (NULL == arr) || (num <= 0))
    {
        printf("%s(%d): invalid input! num=%d.\n", __FUNCTION__, __LINE__, num);
        return INVALID_INPUT;
    }

    *tree = NULL;

    for (pos = 0; pos < num; pos++)
    {
        /* ignore the duplicate elements. */
        result = tree_insert(tree, arr + pos, sizeof(int));
        if ((SUCCESS != result) && (DUPLICATED != result))
        {
            printf("%s(%d): err[%d]: failed to insert tree! data=%d.\n", __FUNCTION__, __LINE__, result, arr[pos]);
            return result;
        }
    }

    return SUCCESS;
}

static void tree_set_x(Tree *tree, int *x)
{
    if (NULL == tree)
    {
        return;
    }
    
    tree_set_x(tree->left, x);

    tree->pos->x = (*x)++;

    tree_set_x(tree->right, x);
}

static void tree_set_y(Tree *tree, int y)
{
    if (NULL == tree)
    {
        return;
    }

    tree->pos->y = y;

    tree_set_y(tree->left, y-1);
    tree_set_y(tree->right, y-1);
}

void tree_set_position(Tree *tree)
{
    int x = 0;

    tree_set_x(tree, &x);

    tree_set_y(tree, 0);
}

static void generate_random_arr(int *arr, int len)
{
    int pos;
    int idx;
    int tmp;

    for (pos = 0; pos < len; pos++)
    {
        arr[pos] = rand() % MAX_TREE_DATA;
    }
}

int tree_random_create(Tree **tree, int num)
{
    int pos;
    int result;
    int *arr = NULL;

    srand((unsigned)time(0));

    arr = malloc(sizeof(int) * num);
    if (NULL == arr)
    {
        printf("%s(%d): failed to malloc memory for arr!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    generate_random_arr(arr, num);

    for (pos = 0; pos < num; pos++)
    {
        result = tree_insert(tree, arr + pos, sizeof(int));
        if ((SUCCESS != result) && (DUPLICATED != result))
        {
            printf("%s(%d): failed to insert tree!\n", __FUNCTION__, __LINE__);
            return result;
        }
    }

    return SUCCESS;
}
