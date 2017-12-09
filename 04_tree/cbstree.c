/* implementation of binary serch tree using cursor */
#include "utils.h"
#include "cbstree.h"

#define ARR_SIZE  1000

struct Node
{
    int data;
    int left;
    int right;
    int next;   
};

typedef struct Node Node;

Node g_arr[ARR_SIZE];

void cursor_init()
{
    int pos;

    memset(g_arr, 0, sizeof(Node) * ARR_SIZE);

    for (pos = 1; pos < ARR_SIZE; pos++)
    {
        g_arr[pos - 1].next = pos;
    }

    g_arr[ARR_SIZE - 1].next = 0;
}

static int cursor_alloc()
{
    int pos;

    pos = g_arr[0].next;
    g_arr[0].next = g_arr[pos].next;

    return pos;
}

static void cursor_free(int pos)
{
    if (0 == pos)
    {
        return;
    }

    memset(g_arr + pos, 0, sizeof(Node));

    g_arr[pos].next = g_arr[0].next;
    g_arr[0].next = pos;
}

Tree tree_init(int data)
{
    int root;

    root = cursor_alloc();
    if (0 == root)
    {
        printf("%s(%d): failed to cursor_alloc for root!\n", __FUNCTION__, __LINE__);
        return 0;
    }

    g_arr[root].data = data;

    return root;
}

/* algorithm for insert:
 * 1. compare current tree's data A with inserted data B,
 * 2. if A == B, return error;
 * 3. if A > B && tree.left == 0, let tree.left = B, return success;
 * 4. if A > B && tree.left > 0, let tree = tree.left, goto 1;
 * 5. if A < B && tree.right == 0, let tree.right = B, return success;
 * 6. if A < B && tree.right > 0, left tree = tree.right, goto 1.
 */
int tree_insert(Tree root, int data)
{
    Tree cur = root;
    Tree node;

    if (root <= 0)
    {
        printf("%s(%d): invalid input! root=%d.\n", __FUNCTION__, __LINE__, root);
        return INVALID_INPUT;
    }

    node = tree_init(data);
    if (0 == node)
    {
        printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
        return MALLOC_FAIL;
    }

    while (0 != cur)
    {
        if (g_arr[cur].data == data)
        {
            printf("%s(%d): data exists! cur=%d, data=%d.\n", __FUNCTION__, __LINE__, cur, data);
            return DUPLICATED;
        }
        else if (g_arr[cur].data > data)
        {
            if (g_arr[cur].left > 0)  /* left child exists */
            {
                cur = g_arr[cur].left;
            }
            else
            {
                g_arr[cur].left = node;
                return SUCCESS;
            }
        }
        else
        {
            if (g_arr[cur].right > 0)
            {
                cur = g_arr[cur].right;
            }
            else
            {
                g_arr[cur].right = node;
                return SUCCESS;
            }
        }
    }
}

Tree tree_find(Tree root, int data)
{
    Tree cur = root;
    Tree parent = root;

    while (0 != cur)
    {
        if (g_arr[cur].data == data)
        {
            /* Here is a skillful trick: use pointer next to refer to parent */
            g_arr[cur].next = parent;
            return cur;
        }
        
        parent = cur;
        cur = (g_arr[cur].data < data)? g_arr[cur].right : g_arr[cur].left;
    }

    return 0;
}

static void tree_replace_with_right_min(Tree root)
{
    Tree parent = root;
    Tree cur = g_arr[root].right;
    Tree right;

    while (0 != g_arr[cur].left)
    {
        parent = cur;
        cur = g_arr[cur].left;
    }

    g_arr[root].data = g_arr[cur].data;

    if (0 == g_arr[cur].right)
    {
        if (cur == g_arr[parent].right)
        {
            g_arr[parent].right = 0;
        }
        else
        {
            g_arr[parent].left = 0;
        }

        cursor_free(cur);
    }
    else
    {
        right = g_arr[cur].right;
        memcpy(g_arr + cur, g_arr + right, sizeof(Node));
        cursor_free(right);
    }
}

/* algorithm for delete:
 * 1. compare current tree's data A with target data B,
 * 2. if A == B, replace current node with  the mininal node of its' right child
 *    and return
 * 3. if A > B, tree = tree.left, goto 1
 * 4. if A < B, tree = tree.right, goto 1
*/
Tree tree_delete(Tree root, int data)
{
    Tree target;
    Tree parent, left, right;

    if (root <= 0)
    {
        printf("%s(%d): invalid input! root=%d, data=%d.\n", __FUNCTION__, __LINE__, root, data);
        return INVALID_TREE;
    }

    /* the position of target's parent is stored in pointer next */
    target = tree_find(root, data);
    if (0 == target)
    {
        printf("%s(%d): not found!\n", __FUNCTION__, __LINE__);
        return root;
    }

    if ((0 == g_arr[target].left) && (0 == g_arr[target].right))
    {
        if (target == root)
        {
            root = 0;
        }
        else
        {
            parent = g_arr[target].next;
            if (g_arr[parent].left == target)
            {
                g_arr[parent].left = 0;
            }
            else
            {
                g_arr[parent].right = 0;
            }
        }

        cursor_free(target);
    }
    else if (0 == g_arr[target].left)
    {
        right = g_arr[target].right;
        memcpy(g_arr + target, g_arr + right, sizeof(Node));
        cursor_free(right);
    }
    else if (0 == g_arr[target].right)
    {
        left = g_arr[target].left;
        memcpy(g_arr + target, g_arr + left, sizeof(Node));
        cursor_free(left);
    }
    else
    {
        tree_replace_with_right_min(target);
    }

    return root;
}

void tree_clear(Tree root)
{
    if (root <= 0)
    {
        return;
    }

    tree_clear(g_arr[root].left);
    tree_clear(g_arr[root].right);
    cursor_free(root);
}

void tree_preorder_print(Tree root)
{
    if (root <= 0)
    {
        return;
    }

    printf("%d ", g_arr[root].data);
    tree_preorder_print(g_arr[root].left);
    tree_preorder_print(g_arr[root].right);
}

void tree_inorder_print(Tree root)
{
    if (root <= 0)
    {
        return;
    }

    tree_inorder_print(g_arr[root].left);
    printf("%d ", g_arr[root].data);
    tree_inorder_print(g_arr[root].right);
}

void tree_postorder_print(Tree root)
{
    if (root <= 0)
    {
        return;
    }

    tree_postorder_print(g_arr[root].left);
    tree_postorder_print(g_arr[root].right);
    printf("%d ", g_arr[root].data);
}
