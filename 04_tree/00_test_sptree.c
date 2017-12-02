#include "utils.h"
#include "sptree.h"

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

void test_tree_init(Tree **tree);
void test_tree_clear(Tree **tree);
void test_tree_insert(Tree **tree);
void test_tree_delete(Tree **tree);
void test_tree_find(Tree **tree);
void test_tree_find_min(Tree **tree);
void test_tree_find_max(Tree **tree);
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
                             test_tree_find,
                             test_tree_find_min,
                             test_tree_find_max,
                             test_tree_preorder_print,
                             test_tree_inorder_print,
                             test_tree_postorder_print
    };

    while (1)
    {
        printf("\n0.init 1.clear 2.insert 3.delete 4.find 5.min 6.max");
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

void test_tree_find(Tree **tree)
{
    int result = SUCCESS;
    int data = 0;
    int left = 0;
    int right = 0;

    printf("\nEnter data you want to find: ");
    scanf("%d", &data);

    result = tree_find(tree, &data, sizeof(int));
    if (SUCCESS != result)
    {
        printf("\ncannot find the node with data %d! result=%d.", data, result);
    }
    else
    {
        left = (NULL == (*tree)->left) ? -1 : (*(int *)(*tree)->left->data);
        right = (NULL == (*tree)->right) ? -1 : (*(int *)(*tree)->right->data);

        printf("\nfind the node with data %d!", data);
        printf("\nleft: %d, right: %d", left, right);
    }
}

void test_tree_find_min(Tree **tree)
{
    int result = SUCCESS;
    Tree *target = NULL;

    result = tree_find_min(*tree, &target);
    if (SUCCESS != result)
    {
        printf("\nfailed to find tree's min! result=%d.", result);
    }
    else
    {
        printf("\ntree's min is %d.", *(int *)target->data);
    }
}

void test_tree_find_max(Tree **tree)
{
    int result = SUCCESS;
    Tree *target = NULL;

    result = tree_find_max(*tree, &target);
    if (SUCCESS != result)
    {
        printf("\nfailed to find tree's max! result=%d.", result);
    }
    else
    {
        printf("\ntree's max is %d.", *(int *)target->data);
    }
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
