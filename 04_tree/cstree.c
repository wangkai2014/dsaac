/* implementation of tree stored with child/sibling link */
#include "utils.h"
#include "queue.h"
#include "cstree.h"

int tree_init(Tree **in_tree, void *data, int data_size)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    if ((NULL == in_tree) || (NULL == data) || (data_size <= 0))
    {
        ERR_MSG("invalid input! data_size=%d.\n", data_size);
        return INVALID_INPUT;
    }

    tree = (Tree *)malloc(sizeof(Tree));
    if (NULL == tree)
    {
        ERR_MSG("failed to malloc memory!\n");
        return MALLOC_FAIL;
    }

    tree->data = malloc(data_size);
    if (NULL == tree->data)
    {
        ERR_MSG("failed to malloc memory!\n");
        return MALLOC_FAIL;
    }

    memcpy(tree->data, data, data_size);

    tree->sibl = NULL;
    tree->child = NULL;

    *in_tree = tree;

    return SUCCESS;
}

int tree_create(Tree **in_tree, Tree *sibl, Tree *child, void *data, int data_size)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    if ((NULL == in_tree) || (NULL == data) || (data_size <= 0))
    {
        ERR_MSG("invaild input! data_size=%d.\n", data_size);
        return INVALID_INPUT;
    }

    tree = (Tree *)malloc(sizeof(Tree));
    if (NULL == tree)
    {
        ERR_MSG("failed to malloc memory!\n");
        return MALLOC_FAIL;
    }

    tree->data = malloc(data_size);
    if (NULL == tree->data)
    {
        ERR_MSG("failed to malloc memory!\n");
        return MALLOC_FAIL;
    }

    memcpy(tree->data, data, data_size);

    tree->sibl = sibl;
    tree->child = child;

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
        ERR_MSG("invalid input! data_size=%d.\n", data_size);
        return INVALID_INPUT;
    } 

    link = tree;
    cur = *tree;

    while (NULL != cur)
    {
        result = cmp_data(data, cur->data, data_size);
        if (0 == result)
        {
            ERR_MSG("the node[%d] has existed!\n", *(int*)data);
            return DUPLICATED;
        }

        if ((result < 0) && (cur->child != NULL) && 
                (cmp_data(cur->data, cur->child->data, data_size) < 0))
        {
            link = &cur->child;
            break;
        }

        link = &cur->child;
        cur = cur->child;

        if ((result > 0) && (cur != NULL))
        {
            link = &cur->sibl;
            cur = cur->sibl;
        }
    }

    result = tree_init(&cur, data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to init tree!\n");
        return result;
    }

    if (*link != NULL)
    {
        cur->sibl = *link;
    }

    *link = cur;

    return SUCCESS;
}

static int tree_delete_min(Tree **tree, Tree **target)
{
    int result = SUCCESS;
    Tree **link = NULL;
    Tree *min = NULL;
    
    if ((NULL == tree) || (NULL == *tree) || (NULL == target))
    {
        ERR_MSG("null pointer!\n");
        return NUL_PTR;
    }

    link = tree;
    min = *tree;
    while (NULL != min->sibl)
    {
        link = &min->sibl;
        min = min->sibl;
    }

    *link = min->child;
    *target = min;
    
    return SUCCESS;
}

/**
 * if root->data == data, *link = &root;
 * if cur->data == data, and cur is parent's sibl child, *link = &parent->sibl
 * if cur->data == data, and cur is parent's child child, *link = &parent->child
 */
int tree_find_parent_link(Tree **tree, Tree ***link, void *data, int data_size)
{
    int result = 0;
    Tree *cur = NULL;

    if ((NULL == tree) || (NULL == link) || (NULL == data) || (data_size <= 0))
    {
        ERR_MSG("invalid input! data_size=%d.\n", data_size);
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
        
        *link = (result < 0) ? &cur->sibl : &cur->child;
        cur = (result < 0) ? cur->sibl : cur->child;
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
        ERR_MSG("invalid input! data_size=%d.\n", data_size);
        return INVALID_INPUT;
    } 

    result = tree_find_parent_link(tree, &link, data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to find parent link!\n");
        return result;
    }

    cur = *link;

    if (NULL == cur->sibl)
    {
        *link = cur->child;
    }
    else if (NULL == cur->child)
    {
        *link = cur->sibl;
    }
    else
    {
        result = tree_delete_min(&cur->child, &min);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to delete min!\n");
            return result;
        }

        min->sibl = cur->sibl;
        min->child = cur->child;
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

    tree_clear(&(*tree)->sibl);
    tree_clear(&(*tree)->child);

    free((*tree)->data);
    free(*tree);
    *tree = NULL;
}

int tree_find(Tree *tree, Tree **target, void *data, int data_size)
{
    int result = 0;
    Tree *cur = tree;

    if ((NULL == tree) || (NULL == target) || (NULL == data) || (data_size <= 0))
    {
        ERR_MSG("null pointer! data_size=%d.\n", data_size);
        return INVALID_INPUT;
    }

    while ((NULL != cur) && (0 != result))
    {
        result = cmp_data(data, cur->data, data_size);

        cur = (result < 0) ? cur->sibl : cur->child;
    }

    *target = cur;

    return SUCCESS;
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
        ERR_MSG("failed to init queue!\n");
        return;
    }

    result = queue_enqueue(queue, &tree, sizeof(Tree *));
    if (SUCCESS != result)
    {
        ERR_MSG("failed to enqueue tree.\n");
        return;
    }

    while (!queue_is_empty(queue))
    {
        result = queue_dequeue(queue, &tree, sizeof(Tree *));
        if (SUCCESS != result)
        {
            ERR_MSG("failed to dequeue tree.\n");
            queue_clear(&queue);
            return;
        }

        printf("%d ", *(int *)tree->data);

        if (NULL != tree->child)
        {
            result = queue_enqueue(queue, &tree->child, sizeof(Tree *));
            if (SUCCESS != result)
            {
                ERR_MSG("failed to enqueue tree.\n");
                queue_clear(&queue);
                return;
            }

            if (NULL != tree->child->sibl)
            {
                result = queue_enqueue(queue, &tree->child->sibl, sizeof(Tree *));
                if (SUCCESS != result)
                {
                    ERR_MSG("failed to enqueue tree.\n");
                    queue_clear(&queue);
                    return;
                }
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
        ERR_MSG("invalid input! num=%d.\n", num);
        return INVALID_INPUT;
    }

    *tree = NULL;

    for (pos = 0; pos < num; pos++)
    {
        /* ignore the duplicate elements. */
        result = tree_insert(tree, arr + pos, sizeof(int));
        if ((SUCCESS != result) && (DUPLICATED != result))
        {
            ERR_MSG("err[%d]: failed to insert tree! data=%d.\n", result, arr[pos]);
            return result;
        }
    }

    return SUCCESS;
}
