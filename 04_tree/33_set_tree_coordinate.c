#include "utils.h"
#include "bstree.h"

void print_bstree_coordinate(Tree *tree);

int main()
{
    int go_on = TRUE;
    int num = 0;
    int result;
    Tree *tree = NULL;

    while (go_on == TRUE)
    {
        printf("\nEnter node's num: ");
        scanf("%d", &num);

        result = tree_random_create(&tree, num);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to create random bstree!\n", __FUNCTION__, __LINE__);
            return result;
        }

        tree_set_position(tree);

        printf("\npreorder visit the tree:\n");
        print_bstree_coordinate(tree);

        tree_clear(&tree);

        printf("\ncontinue?(0.no 1.yes): ");
        scanf("%d", &go_on);
    }

    return 0;
}

void print_bstree_coordinate(Tree *tree)
{
    int data;
    int x, y;

    if (NULL == tree)
    {
        return;
    }

    data = *((int *)tree->data);

    printf("%d(%d,%d) ", data, tree->pos->x, tree->pos->y);

    print_bstree_coordinate(tree->left);

    print_bstree_coordinate(tree->right);
}
