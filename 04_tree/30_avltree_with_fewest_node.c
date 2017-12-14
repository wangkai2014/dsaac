#include "utils.h"
#include "bstree.h"

int randint(int a, int b);
int power(int base, int expo);
int make_bstree(Tree **tree, int min, int max, int height);

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

        if (height < 2)
        {
            printf("invalid height. bye~bye~\n");
            return 0;
        }

        make_bstree(&tree, 1, power(2, height+1) - 1, height);

        printf("preorder visit:\n");
        tree_preorder_print_int(tree);

        printf("\npostorder visit:\n");
        tree_postorder_print_int(tree);

        printf("\n\n");

        tree_clear(&tree);
    }
}

int randint(int a, int b)
{
    return ( a + rand() % (b - a + 1));
}

int power(int base, int expo)
{
    int result = base;

    while (--expo)
    {
        result *= base;
    }

    return result;
}

int make_bstree(Tree **tree, int min, int max, int height)
{
    int result;
    int data = (min + max) / 2;

    if (0 == height)
    {
        return tree_init(tree, &data, sizeof(int));
    }
    else if (1 == height)
    {
        result = tree_init(tree, &data, sizeof(int));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
            return result;
        }

        return tree_init(&(*tree)->left, &min, sizeof(int));
    }
    else
    {
        result = tree_init(tree, &data, sizeof(int));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = make_bstree(&(*tree)->left, min, data - 1, height - 1);
        result |= make_bstree(&(*tree)->right, data + 1, max, height - 2);

        return result;
    }
}
