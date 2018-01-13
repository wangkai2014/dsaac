#include "utils.h"
#include "bstree.h"

int get_tree_data(Tree** tree);
int tree_transform(Tree **first, Tree *second);
int tree_rotate_to_root(Tree **first, Tree *second);
int cmp_tree_data(Tree *first, Tree *second);

int main()
{
    int go_on = 1;
    int result = SUCCESS;
    Tree *first = NULL;
    Tree *second = NULL;

    while (go_on)
    {
        printf("\n**********Tree 1**********");

        result = get_tree_data(&first);
        if (SUCCESS != result)
        {
            ERR_MSG("\nerr(%d): failed to get first tree's data!\n", result);
            return result;
        }

        printf("\npreorder visit tree 1: ");
        tree_preorder_print_int(first);

        printf("\n\n**********Tree 2**********");

        result = get_tree_data(&second);
        if (SUCCESS != result)
        {
            ERR_MSG("\nerr(%d): failed to get second tree's data!\n", result);
            return result;
        }

        printf("\npreorder visit tree 2: ");
        tree_preorder_print_int(second);

        result = tree_transform(&first, second);
        if (SUCCESS != result)
        {
            ERR_MSG("\nerr(%d): failed to transform tree!\n", result);
            return result;
        }

        printf("\n\n*****after transform*****");
        printf("\npreorder visit tree 1: ");
        tree_preorder_print_int(first);
        printf("\n");

        tree_clear(&first);
        tree_clear(&second);

        printf("\n\nContinue?(0.no 1.yes): ");
        scanf("%d", &go_on);
    }

    return 0;
}

int get_tree_data(Tree **tree)
{
    int pos;
    int num = 0;
    int result = SUCCESS;
    int *arr = NULL;

    printf("\nEnter num: ");
    scanf("%d", &num);
    printf("Enter data: ");

    arr = (int *)malloc(sizeof(int) * num);
    if (NULL == arr)
    {
        ERR_MSG("\nfailed to malloc memory for arr!\n");
        return MALLOC_FAIL;
    }

    for (pos = 0; pos < num; pos++)
    {
        scanf("%d", arr + pos);
    }

    result = tree_init_by_int_arr(tree, arr, num);
    if (SUCCESS != result)
    {
        ERR_MSG("\nerr(%d): failed to init tree by int array!\n", result);
    }

    free(arr);

    return result;
}

int tree_transform(Tree **first, Tree *second)
{
    int result = SUCCESS;

    if ((NULL == *first) || (NULL == second))
    {
        return SUCCESS;
    }

    if (cmp_tree_data(*first, second) != 0)
    {
        result = tree_rotate_to_root(first, second);
        if (SUCCESS != result)
        {
            ERR_MSG("\nerr(%d): failed to rotate to root!\n", result);
            return result;
        }
    }

    result = tree_transform(&(*first)->left, second->left);
    result |= tree_transform(&(*first)->right, second->right);

    return result;
}

int tree_rotate_to_root(Tree **first, Tree *second)
{
    int cmp_result = 0;
    int result = SUCCESS;
    Tree *left = NULL;
    Tree *right = NULL;

    cmp_result = cmp_tree_data(*first, second);

    if (cmp_result > 0)
    {
        if (cmp_tree_data((*first)->left, second) != 0)
        {
            result = tree_rotate_to_root(&(*first)->left, second);
            if (SUCCESS != result)
            {
                ERR_MSG("\nerr(%d): failed to rotate to root!\n", result);
                return result;
            }
        }

        /* single right rotate*/
        left = (*first)->left;
        (*first)->left = left->right;
        left->right = *first;
        *first = left;
    }
    else if (cmp_result < 0)
    {
        if (cmp_tree_data((*first)->right, second) != 0)
        {
            result = tree_rotate_to_root(&(*first)->right, second);
            if (SUCCESS != result)
            {
                ERR_MSG("\nerr(%d): failed to rotate to root!\n", result);
                return result;
            }
        }

        /* single left rotate*/
        right = (*first)->right;
        (*first)->right = right->left;
        right->left = *first;
        *first = right;
    }

    return SUCCESS;
}

int cmp_tree_data(Tree *first, Tree *second)
{
    int a,b;
    
    if ((NULL == first) || (NULL == second))
    {
        return -1;
    }

    a = *(int*)first->data;
    b = *(int*)second->data;

    return ((a < b) ? -1 : ((a > b) ? 1 : 0));
}
