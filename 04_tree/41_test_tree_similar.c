#include "utils.h"
#include "bstree.h"

void get_tree_data(int **arr, int *num);
int tree_is_similar(Tree *first, Tree *second);

int main()
{
    int go_on = 1;
    int *arr;
    int num = 0;
    int result = SUCCESS;
    Tree *first = NULL;
    Tree *second = NULL;

    while (go_on)
    {
        printf("\n**********Tree 1**********");
        get_tree_data(&arr, &num);

        result = tree_init_by_int_arr(&first, arr, num);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to init first tree!\n");
            return result;
        }

        free(arr);
        printf("\n**********Tree 2**********");
        get_tree_data(&arr, &num);

        result = tree_init_by_int_arr(&second, arr, num);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to init second tree!\n");
            return result;
        }

        free(arr);

        if (tree_is_similar(first, second))
        {
            printf("\nThe two trees are similar.");
        }
        else
        {
            printf("\nThe two trees are not similar.");
        }

        tree_clear(&first);
        tree_clear(&second);

        printf("\n\nContinue?(0.no 1.yes): ");
        scanf("%d", &go_on);
    }

    return 0;
}

void get_tree_data(int **arr, int *num)
{
    int pos;
    int size = 0;
    int *data = NULL;

    printf("\nEnter size: ");
    scanf("%d", &size);
    printf("Enter data: ");

    data = (int *)malloc(sizeof(int) * size);
    if (NULL == data)
    {
        ERR_MSG("failed to malloc memory for data!\n");
        return;
    }

    for (pos = 0; pos < size; pos++)
    {
        scanf("%d", data + pos);
    }

    *arr = data;
    *num = size;
}

int tree_is_similar(Tree *first, Tree *second)
{
    if ((NULL == first) && (NULL == second))
    {
        return TRUE;
    }
    else if ((NULL != first) && (NULL != second))
    {
        return ((tree_is_similar(first->left, second->left)) &&
                (tree_is_similar(first->right, second->right)));
    }
    else
    {
        return FALSE;
    }
}
