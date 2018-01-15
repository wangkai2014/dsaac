#include "utils.h"
#include "bstree.h"

enum OPER_CODE
{
    INIT         = 0,
    CLEAR        = 1,
    INSERT       = 2,
    DELETE       = 3,
    PRE_PRINT    = 4,
    IN_PRINT     = 5,
    POST_PRINT   = 6,
    LEVEL_PRINT  = 7,
    FIND         = 8,
    QUIT
};

typedef void (*FUNC_PTR)(Tree **);

int tree_find_Kth(Tree *tree, int sequ_id, int *data);
void test_tree_init(Tree **tree);
void test_tree_clear(Tree **tree);
void test_tree_insert(Tree **tree);
void test_tree_delete(Tree **tree);
void test_tree_find(Tree **tree);
void test_tree_preorder_print(Tree **tree);
void test_tree_inorder_print(Tree **tree);
void test_tree_postorder_print(Tree **tree);
void test_tree_levelorder_print(Tree **tree);

int main()
{
    int oper = 0;
    Tree *tree = NULL;
    FUNC_PTR test_func[] = { test_tree_init,
                             test_tree_clear,
                             test_tree_insert,
                             test_tree_delete,
                             test_tree_preorder_print,
                             test_tree_inorder_print,
                             test_tree_postorder_print,
                             test_tree_levelorder_print,
                             test_tree_find
    };

    while (1)
    {
        printf("\n0.init 1.clear 2.insert 3.delete 4.pre 5.in 6.post 7.level 8.find 9.quit");
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
    int *data = NULL;

    printf("\nEnter node's num you want to insert: ");
    scanf("%d", &num);
    printf("Enter data: ");

    for (pos = 0; pos < num; pos++)
    {
        data = (int *)malloc(sizeof(int));
        if (NULL == data)
        {
            ERR_MSG("failed to malloc memory for data!\n");
            return;
        }

        scanf("%d", data);

        result = tree_insert(tree, data, sizeof(int));
        if ((SUCCESS != result) && (DUPLICATED != result))
        {
            ERR_MSG("\nerr %d: failed to insert %d to tree!", result, *data);
            return;
        }
    }

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
    int sequ_id = 0;
    int data = 0;

    printf("\nEnter node's sequence id you want to find: ");
    scanf("%d", &sequ_id);

    result = tree_find_Kth(*tree, sequ_id, &data);
    if (SUCCESS != result)
    {
        ERR_MSG("\nfailed to find the %dth data!", sequ_id);
        return;
    }

    printf("\nthe %dth data is %d.\n", sequ_id, data);
}

int tree_find_Kth(Tree *tree, int sequ_id, int *data)
{
    Tree *cur = tree;
    int inorder_id;

    if ((NULL == tree) || (NULL == data) || (sequ_id < 1))
    {
        ERR_MSG("invalid input! sequ_id=%d.\n", sequ_id);
        return INVALID_INPUT;
    }

    while (NULL != cur)
    {
        inorder_id = (NULL == cur->left)? 1 : (cur->left->node_num + 1);

        if (inorder_id == sequ_id)
        {
            *data = *(int*)cur->data;
            return SUCCESS;
        }
        else if (inorder_id < sequ_id)
        {
            sequ_id -= inorder_id;
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }

    return NOT_FOUND;
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

void test_tree_levelorder_print(Tree **tree)
{
    printf("\nlevelorder visit the tree:\n");

    tree_levelorder_print_int(*tree);

    printf("\n");
}
