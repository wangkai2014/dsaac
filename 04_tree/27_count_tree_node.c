#include "utils.h"
#include "bstree.h"

enum OPER_CODE
{
    INIT         = 0,
    CLEAR        = 1,
    INSERT       = 2,
    DELETE       = 3,
    FIND         = 4,
    FIND_MIN     = 5,
    FIND_MAX     = 6,
    PRE_PRINT    = 7,
    IN_PRINT     = 8,
    POST_PRINT   = 9,
    QUIT
};

typedef void (*FUNC_PTR)(Tree **);

int tree_node_num(Tree *tree);
int tree_leaf_num(Tree *tree);
int tree_full_node_num(Tree *tree);
void test_tree_init(Tree **tree);
void test_tree_clear(Tree **tree);
void test_tree_insert(Tree **tree);
void test_tree_delete(Tree **tree);
void test_tree_node_num(Tree **tree);
void test_tree_leaf_num(Tree **tree);
void test_tree_full_node_num(Tree **tree);
void test_tree_preorder_print(Tree **tree);
void test_tree_inorder_print(Tree **tree);
void test_tree_postorder_print(Tree **tree);

int main()
{
    int oper = 0;
    Tree *tree = NULL;
    FUNC_PTR test_func[] = { test_tree_init,
                             test_tree_clear,
                             test_tree_insert,
                             test_tree_delete,
                             test_tree_node_num,
                             test_tree_leaf_num,
                             test_tree_full_node_num,
                             test_tree_preorder_print,
                             test_tree_inorder_print,
                             test_tree_postorder_print
    };

    while (1)
    {
        printf("\n0.init 1.clear 2.insert 3.delete 4.node_num 5.leaf_num 6.full_num");
        printf("\n7.preorder_print 8.inorder_print 9.postorder_print 10.quit");
        printf("\nEnter operation: ");
        scanf("%d", &oper);

        if (oper >= QUIT)
        {
            break;
        }

        (test_func[oper])(&tree);

        printf("\n");
    }

    tree_clear(&tree);

    return 0;
}

void test_tree_init(Tree **tree)
{
    int result = SUCCESS;
    int data = 0;

    result = tree_init(tree, &data, sizeof(int));
    if (SUCCESS != result)
    {
        printf("\nfailed to init tree! result=%d.", result);
    }
    else
    {
        printf("\ninit tree successfully!");
    }
}

void test_tree_clear(Tree **tree)
{
    tree_clear(tree);

    printf("\nclear tree successfully!");
}

void test_tree_insert(Tree **tree)
{
    int result = SUCCESS;
    int num = 0;
    int pos = 0;
    int *arr = NULL;

    printf("\nEnter node's num you want to insert: ");
    scanf("%d", &num);
    printf("Enter data: ");

    arr = (int *)malloc(sizeof(int) * num);
    if (NULL == arr)
    {
        printf("\n%s(%d): failed to malloc memory for arr!", __FUNCTION__, __LINE__);
        return;
    }

    for (pos = 0; pos < num; pos++)
    {
        scanf("%d", arr + pos);
    }

    for (pos = 0; pos < num; pos++)
    {
        result = tree_insert(tree, arr + pos, sizeof(int));
        if (SUCCESS != result)
        {
            printf("\n%s(%d): failed to insert %d to tree!", __FUNCTION__, __LINE__, arr[pos]);
            free(arr);
            return;
        }
    }

    free(arr);

    printf("\ninsert successfully!");
}

void test_tree_delete(Tree **tree)
{
    int result = SUCCESS;
    int num = 0;
    int pos = 0;
    int *arr = NULL;

    printf("\nEnter node's num you want to delete: ");
    scanf("%d", &num);
    printf("Enter data: ");

    arr = (int *)malloc(sizeof(int) * num);
    if (NULL == arr)
    {
        printf("\n%s(%d): failed to malloc memory for arr!", __FUNCTION__, __LINE__);
        return;
    }

    for (pos = 0; pos < num; pos++)
    {
        scanf("%d", arr + pos);
    }

    for (pos = 0; pos < num; pos++)
    {
        result = tree_delete(tree, arr + pos, sizeof(int));
        if (SUCCESS != result)
        {
            printf("\n%s(%d): failed to delete %d!", __FUNCTION__, __LINE__, arr[pos]);
            free(arr);
            return;
        }
    }

    free(arr);

    printf("\ndelete successfully!");
}

int tree_node_num(Tree *tree)
{
    if (NULL == tree)
    {
        return 0;
    }
    else
    {
        return (tree_node_num(tree->left) + tree_node_num(tree->right) + 1);
    }
}

int tree_leaf_num(Tree *tree)
{
    if (NULL == tree)
    {
        return 0;
    }
    else if ((NULL == tree->left) && (NULL == tree->right))
    {
        return 1;
    }
    else
    {
        return (tree_leaf_num(tree->left) + tree_leaf_num(tree->right));
    }
}

int tree_full_node_num(Tree *tree)
{
    if (NULL == tree)
    {
        return 0;
    }
    else if ((NULL != tree->left) && (NULL != tree->right))
    {
        return (tree_full_node_num(tree->left) + tree_full_node_num(tree->right) + 1);
    }
    else
    {
        return (tree_full_node_num(tree->left) + tree_full_node_num(tree->right));
    }
}

void test_tree_node_num(Tree **tree)
{
    printf("\nnode num: %d.\n", tree_node_num(*tree));
}

void test_tree_leaf_num(Tree **tree)
{
    printf("\nleaf num: %d.\n", tree_leaf_num(*tree));
}

void test_tree_full_node_num(Tree **tree)
{
    printf("\nfull node num: %d.\n", tree_full_node_num(*tree));
}

void test_tree_preorder_print(Tree **tree)
{
    printf("\npreorder visit the tree:\n");

    tree_preorder_print_int(*tree);

    printf("\n");
}

void test_tree_inorder_print(Tree **tree)
{
    printf("\ninorder visit the tree:\n");

    tree_inorder_print_int(*tree);

    printf("\n");
}

void test_tree_postorder_print(Tree **tree)
{
    printf("\npostorder visit the tree:\n");

    tree_postorder_print_int(*tree);

    printf("\n");
}
