#include "utils.h"
#include "bstree.h"

void generate_random_arr(int *arr, int len);

int main()
{
    int go_on = TRUE;
    int num = 0;
    int pos;
    int result;
    int *arr = NULL;
    Tree *tree = NULL;

    srand((unsigned)time(0));

    while (go_on == TRUE)
    {
        printf("\nEnter node's num: ");
        scanf("%d", &num);

        arr = malloc(sizeof(int) * num);
        if (NULL == arr)
        {
            printf("%s(%d): failed to malloc memory for arr!\n", __FUNCTION__, __LINE__);
            return MALLOC_FAIL;
        }

        generate_random_arr(arr, num);

        for (pos = 0; pos < num; pos++)
        {
            result = tree_insert(&tree, arr + pos, sizeof(int));
            if (SUCCESS != result)
            {
                printf("%s(%d): failed to insert tree!\n", __FUNCTION__, __LINE__);
                return result;
            }
        }

        printf("preorder visit:\n");
        tree_preorder_print_int(tree);

        printf("\npostorder visit:\n");
        tree_postorder_print_int(tree);

        tree_clear(&tree);
        free(arr);

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
        arr[pos] = pos + 1;
    }

    for (pos = len; pos > 0; pos--)
    {
        idx = rand() % pos;
        tmp = arr[idx];
        arr[idx] =arr[pos-1];
        arr[pos-1] = tmp;
    }
}
