#include "utils.h"
#include "cbstree.h"

enum OPER_CODE
{
    INIT         = 0,
    CLEAR        = 1,
    INSERT       = 2,
    DELETE       = 3,
    FIND         = 4,
    PRE_PRINT    = 5,
    IN_PRINT     = 6,
    POST_PRINT   = 7,
    QUIT
};

typedef void (*FUNC_PTR)();

void test_tree_init();
void test_tree_clear();
void test_tree_insert();
void test_tree_delete();
void test_tree_find();
void test_tree_preorder_print();
void test_tree_inorder_print();
void test_tree_postorder_print();

Tree g_tree = 0;

int main()
{
    int oper = 0;
    FUNC_PTR test_func[] = { test_tree_init,
                             test_tree_clear,
                             test_tree_insert,
                             test_tree_delete,
                             test_tree_find,
                             test_tree_preorder_print,
                             test_tree_inorder_print,
                             test_tree_postorder_print
    };

    cursor_init();

    while (1)
    {
        printf("\n0.init 1.clear 2.insert 3.delete 4.find");
        printf("\n5.preorder_print 6.inorder_print 7.postorder_print 8.quit");
        printf("\nEnter operation: ");
        scanf("%d", &oper);

        if (oper >= QUIT)
        {
            break;
        }

        (test_func[oper])();

        printf("\n");
    }

    tree_clear(g_tree);

    return 0;
}

void test_tree_init()
{
    int result = SUCCESS;
    int data = 0;

    printf("\nEnter data: ");
    scanf("%d", &data);

    g_tree = tree_init(data);
    if (0 == g_tree)
    {
        printf("failed to init tree! result=%d.", result);
    }
    else
    {
        printf("init tree successfully!");
    }
}

void test_tree_clear()
{
    tree_clear(g_tree);
    g_tree = 0;

    printf("\nclear tree successfully!");
}

void test_tree_insert()
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
        result = tree_insert(g_tree, arr[pos]);
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

void test_tree_delete()
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
        g_tree = tree_delete(g_tree, arr[pos]);
        if (INVALID_TREE == g_tree)
        {
            g_tree = 0;
            printf("\n%s(%d): failed to delete %d!", __FUNCTION__, __LINE__, arr[pos]);
            free(arr);
            return;
        }
    }

    free(arr);

    printf("\ndelete successfully!");
}

void test_tree_find()
{
    int data = 0;
    Tree target;

    printf("\nEnter data you want to find: ");
    scanf("%d", &data);

    target = tree_find(g_tree, data);
    if (0 == target)
    {
        printf("\ncannot find the node with data %d!", data);
    }
    else
    {
        printf("\nfind the node with data %d!", data);
    }
}

void test_tree_preorder_print()
{
    printf("\npreorder visit the tree:\n");
    tree_preorder_print(g_tree);
}

void test_tree_inorder_print()
{
    printf("\ninorder visit the tree:\n");
    tree_inorder_print(g_tree);
}

void test_tree_postorder_print()
{
    printf("\npostorder visit the tree:\n");
    tree_postorder_print(g_tree);
}
