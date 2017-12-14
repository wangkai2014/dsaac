#include "utils.h"
#include "bstree.h"

int randint(int a, int b);
int make_bstree(Tree **tree, int a, int b);

int main()
{
    int num = 0;
    int result;
    Tree *tree = NULL;

    srand((unsigned)time(0));

    while (1)
    {
        printf("Enter node's num: ");
        scanf("%d", &num);

        if (num <= 0)
        {
            printf("invalid num. bye~bye~\n");
            return 0;
        }

        make_bstree(&tree, 1, num);

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

int make_bstree(Tree **tree, int a, int b)
{
    int result;
    int data;

    if (a > b)
    {
        return SUCCESS;
    }
    else
    {
        data = randint(a, b);

        result = tree_init(tree, &data, sizeof(int));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = make_bstree(&(*tree)->left, a, data - 1);
        result |= make_bstree(&(*tree)->right, data + 1, b);

        return result;
    }
}
