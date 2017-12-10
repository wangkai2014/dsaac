#include "utils.h"
#include "bstree.h"

#define TREE_NUM  3
#define TEST_NUM  100
#define NODE_NUM  100   /* number of tree's node */
#define MAX_DATA  10000

typedef int (*FUNC_PTR)(Tree **tree);

int test_tree_delete(Tree **tree, int tree_id, int del_time);
int tree_delete_root(Tree **tree, int tree_id);
int tree_delete_left(Tree **tree);
int tree_delete_alternate(Tree **tree);
int tree_delete_random(Tree **tree);

int tree_replace_left(Tree **tree);
int tree_replace_right(Tree **tree);

void set_array(int *arr, int num);
void print_array(int *arr, int num);

int main()
{
    int tree_id;
    int test_id;
    int result;
    int arr[NODE_NUM];
    Tree *tree[TREE_NUM];

    srand((unsigned)time(0));

    for (test_id = 0; test_id < TEST_NUM; test_id++)
    {
        printf("\n**************** test %d ****************\n", test_id);

        set_array(arr, NODE_NUM);

        for (tree_id = 0; tree_id < TREE_NUM; tree_id++)
        {
            result = tree_init_by_int_arr(tree + tree_id, arr, NODE_NUM);
            if (SUCCESS != result)
            {
                printf("%s(%d): failed to init tree by int array! test[%d], tree[%d].\n", __FUNCTION__, __LINE__, test_id, tree_id);
                return result;
            }

            result = test_tree_delete(tree + tree_id, tree_id, NODE_NUM/4);
            if (SUCCESS != result)
            {
                printf("%s(%d): failed to test tree delete! test[%d], tree[%d].\n", __FUNCTION__, __LINE__, test_id, tree_id);
                return result;
            }

            tree_clear(tree + tree_id);
        }
    }

    return 0;
}

void set_array(int *arr, int num)
{
    int pos;

    for (pos = 0; pos < num; pos++)
    {
        arr[pos] = (rand() % MAX_DATA) + rand() % 17;
    }
}

void print_array(int *arr, int num)
{
    int pos;

    printf("\ntree's data:\n");

    for (pos = 0; pos < num; pos++)
    {
        printf("%d ", arr[pos]);
    }

    printf("\n\n");
}

int test_tree_delete(Tree **tree, int tree_id, int del_time)
{
    int time;
    int result;
    int cur_ipl;
    int ttl_ipl = 0;
    char method[3][15] = {"1.left:\0", "2.alternate:\0", "3.random:\0"};

    printf("%s\n", method[tree_id]);

    for (time = 0; time < del_time; time++)
    {
        result = tree_delete_root(tree, tree_id);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to delete tree[%d]! time=%d.\n", __FUNCTION__, __LINE__, tree_id, time);
            return result;
        }

        cur_ipl = tree_internal_path_len(*tree);
        ttl_ipl += cur_ipl;

        printf("%d ", cur_ipl);
    }

    printf("\naverage ipl: %d.\n\n", ttl_ipl / del_time);

    return SUCCESS;
}

int tree_delete_root(Tree **in_tree, int tree_id)
{
    int result = SUCCESS;
    Tree *tree = *in_tree;
    FUNC_PTR func[] = {tree_delete_left, tree_delete_alternate, tree_delete_random};
    FUNC_PTR tree_del = func[tree_id];

    if (NULL == tree)
    {
        printf("%s(%d): cannot delete empty tree!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    if ((NULL == tree->left) && (NULL == tree->right))
    {
        *in_tree = NULL;
    }
    else if (NULL == tree->left)
    {
        *in_tree = tree->right;
    }
    else if (NULL == tree->right)
    {
        *in_tree = tree->left;
    }
    else
    {
        result = tree_del(in_tree);
    }

    free(tree->data);
    free(tree);

    return result;
}

int tree_delete_left(Tree **in_tree)
{
    return tree_replace_left(in_tree);
}

int tree_delete_alternate(Tree **in_tree)
{
    static int flag = 0;

    flag = ((flag == 0)? 1 : 0);

    if (flag)
    {
        return tree_replace_left(in_tree);
    }
    else
    {
        return tree_replace_right(in_tree);
    }
}

int tree_delete_random(Tree **in_tree)
{
    int flag = rand() % 2;

    if (flag)
    {
        return tree_replace_left(in_tree);
    }
    else
    {
        return tree_replace_right(in_tree);
    }
}

/* replace root with left child's lastest node */
int tree_replace_left(Tree **tree)
{
    Tree *cur = (*tree)->left;
    Tree **link = &((*tree)->left);

    while (NULL != cur->right)
    {
        link = &(cur->right);
        cur = cur->right;
    }

    *link = cur->left;
    cur->left = (*tree)->left;
    cur->right = (*tree)->right;
    *tree = cur;

    return SUCCESS;
}

/* replace root with right child's smallest node */
int tree_replace_right(Tree **tree)
{
    Tree *cur = (*tree)->right;
    Tree **link = &((*tree)->right);

    while (NULL != cur->left)
    {
        link = &(cur->left);
        cur = cur->left;
    }

    *link = cur->right;
    cur->left = (*tree)->left;
    cur->right = (*tree)->right;
    *tree = cur;

    return SUCCESS;
}
