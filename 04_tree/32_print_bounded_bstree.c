#include "utils.h"
#include "bstree.h"

#define MAX_DATA 100000

void generate_random_arr(int *arr, int len);
int create_random_bstree(Tree **tree, int num);
void print_bounded_bstree(Tree *tree, int min, int max);

int main()
{
    int go_on = TRUE;
    int num = 0;
    int min = 0;
    int max = 0;
    int result;
    Tree *tree = NULL;

    while (go_on == TRUE)
    {
        printf("\nEnter node's num, minimum and maximum: ");
        scanf("%d %d %d", &num, &min, &max);

        result = create_random_bstree(&tree, num);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to create random bstree!\n", __FUNCTION__, __LINE__);
            return result;
        }

        printf("\ninorder visit the bstree:\n");
        tree_inorder_print_int(tree);

        printf("\nthe node between %d and %d:\n", min, max);
        print_bounded_bstree(tree, min, max);

        tree_clear(&tree);

        printf("\ncontinue?(0.no 1.yes): ");
        scanf("%d", &go_on);
    }

    return 0;
}

void generate_random_arr(int *arr, int len)
{
    int pos;
    int idx;
    int tmp;

    for (pos = 0; pos < len; pos++)
    {
        arr[pos] = rand() % MAX_DATA;
    }
}

int create_random_bstree(Tree **tree, int num)
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

void print_bounded_bstree(Tree *tree, int min, int max)
{
    int data;

    if (NULL == tree)
    {
        return;
    }

    data = *((int *)tree->data);

    if ((NULL != tree->left) && (min < data))
    {
        print_bounded_bstree(tree->left, min, max);
    }

    if ((data >= min) && (data <= max))
    {
        printf("%d ", data);
    }

    if ((NULL != tree->right) && (max > data))
    {
        print_bounded_bstree(tree->right, min, max);
    }
}
