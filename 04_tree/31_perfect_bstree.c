#include "utils.h"
#include "bstree.h"

int power(int base, int expo);
int make_perfect_bstree(Tree **tree, int data, int height);

int main()
{
    int height = 0;
    int result;
    Tree *tree = NULL;

    srand((unsigned)time(0));

    while (1)
    {
        printf("Enter tree's height: ");
        scanf("%d", &height);

        if (height < 1)
        {
            printf("invalid height. bye~bye~\n");
            return 0;
        }

        make_perfect_bstree(&tree, power(2, height), height);

        printf("preorder visit:\n");
        tree_preorder_print_int(tree);

        printf("\npostorder visit:\n");
        tree_postorder_print_int(tree);

        printf("\n\n");

        tree_clear(&tree);
    }
}

int power(int base, int expo)
{
    int result = 1;

    while (expo-- > 0)
    {
        result *= base;
    }

    return result;
}

int make_perfect_bstree(Tree **tree, int data, int height)
{
    int result;
    int delta = power(2, height - 1);

    result = tree_init(tree, &data, sizeof(int));
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
    }

    if (height > 0)
    {
        result |= make_perfect_bstree(&(*tree)->left, data - delta, height - 1);
        result |= make_perfect_bstree(&(*tree)->right, data + delta, height - 1);
    }

    return result;
}
