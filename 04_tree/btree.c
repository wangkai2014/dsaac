#include "utils.h"
#include "queue.h"
#include "btree.h"

#define tree_is_leaf(t)  (NULL == (t)->child[0])
#define cmp_data(a, b)  (((*(int*)(a)) < (*(int*)(b))) ? -1 : ((*(int*)(a)) == (*(int*)(b))) ? 0 : 1)

int tree_init(Tree **tree)
{
    if (NULL == tree)
    {
        ERR_MSG("null pointer!\n");
        return NUL_PTR;
    }

    *tree = (Tree *)malloc(sizeof(Tree));
    if (NULL == *tree)
    {
        ERR_MSG("failed to malloc memory!\n");
        return MALLOC_FAIL;
    }

    memset(*tree, 0, sizeof(Tree));

    return SUCCESS;
}

int tree_create_with_data(Tree **tree, Data **data, int num)
{
    if ((NULL == tree) || (NULL == data) || (num < 0))
    {
        ERR_MSG("invalid input! num=%d.\n", num);
        return INVALID_INPUT;
    }

    *tree = (Tree *)malloc(sizeof(Tree));
    if (NULL == *tree)
    {
        ERR_MSG("failed to malloc memory!\n");
        return MALLOC_FAIL;
    }

    memset(*tree, 0, sizeof(Tree));

    while (--num >= 0)
    {
        (*tree)->data[num] = data[num];
    }

    return SUCCESS;
}

static int tree_last_child_pos(Tree *tree)
{
    int pos;

    for (pos = ORDER; (pos >= 0) && (tree->child[pos] == NULL); pos--);

    return pos;
}

static int tree_last_data_pos(Tree *tree)
{
    int pos;

    for (pos = ORDER; (pos >= 0) && (tree->data[pos] == NULL); pos--);

    return pos;
}

static int tree_insert_directly(Tree **in_tree, Data *in_data, Tree **leaf)
{
    int pos;
    Tree *tree = *in_tree;

    if ((NULL == *in_tree) || (NULL == in_data) || (NULL == leaf))
    {
        ERR_MSG("null pointer!\n");
        return NUL_PTR;
    }

    /* find the target leaf to insert the data */
    while (!tree_is_leaf(tree))
    {
        pos = 0;
        while ((NULL != tree->data[pos]) && 
               (cmp_data(tree->data[pos], in_data) < 0))
        {
            pos++;
        }

        tree = tree->child[pos];
    }

    pos = tree_last_data_pos(tree);

    /* find the suitable position to insert data */
    for (; (pos >= 0) && (cmp_data(tree->data[pos], in_data) > 0); pos--)
    {
        tree->data[pos + 1] = tree->data[pos]; 
    }

    tree->data[pos + 1] = in_data;

    *leaf = tree;

    return SUCCESS;
}

static int tree_child_num(Tree *tree)
{
    int pos;

    for (pos = 0; pos <= ORDER; pos++)
    {
        if (NULL == tree->data[pos])
        {
            break;
        }
    }

    return (tree_is_leaf(tree) ? pos : (pos + 1));
}

static Data *tree_min_data(Tree *tree)
{
    while (!tree_is_leaf(tree))
    {
        tree = tree->child[0];
    }

    return tree->data[0];
}

static int tree_leaf_split(Tree *leaf)
{
    int result;
    int pos;

    if (NULL == leaf->parent)  /* leaf is root */
    {
        result = tree_init(leaf->child);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to init child[0]! result=%d.\n", result);
            return result;
        }

        leaf->child[0]->parent = leaf;
        leaf->child[0]->data[0] = leaf->data[0];
        leaf->child[0]->data[1] = leaf->data[1];

        result = tree_init(leaf->child + 1);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to init child[1]! result=%d.\n", result);
            return result;
        }

        leaf->child[1]->parent = leaf;
        leaf->child[1]->data[0] = leaf->data[2];
        leaf->child[1]->data[1] = leaf->data[3];

        memset(leaf->data, 0, sizeof(Data *) * (ORDER + 1));
        leaf->data[0] = leaf->child[1]->data[0];
    }
    else
    {
        pos = tree_last_child_pos(leaf->parent);

        for (; (pos >=0) && (leaf->parent->child[pos] != leaf); pos--)
        {
            leaf->parent->child[pos + 1] = leaf->parent->child[pos];
            leaf->parent->data[pos] = leaf->parent->child[pos]->data[0];
        }

        result = tree_init(leaf->parent->child + pos + 1);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to init child[%d]! result=%d.\n", pos + 1, result);
            return result;
        }

        leaf->parent->child[pos + 1]->parent = leaf->parent;
        leaf->parent->child[pos + 1]->data[0] = leaf->data[2];
        leaf->parent->child[pos + 1]->data[1] = leaf->data[3];
        leaf->parent->data[pos] = leaf->data[2];
        leaf->data[2] = NULL;
        leaf->data[3] = NULL;
    }

    return SUCCESS;
}

static int tree_nonleaf_split(Tree **in_tree, Tree *nonleaf)
{
    int result;
    int pos;
    Tree *tree = NULL;

    while ((NULL != nonleaf) && (tree_child_num(nonleaf) > ORDER))
    {
        result = tree_init(&tree);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to init child[1]! result=%d.\n", result);
            return result;
        }

        tree->child[0] = nonleaf->child[2];
        tree->child[1] = nonleaf->child[3];
        tree->child[0]->parent = tree;
        tree->child[1]->parent = tree;
        tree->data[0] = tree_min_data(tree->child[1]);

        nonleaf->child[2] = NULL;
        nonleaf->child[3] = NULL;
        nonleaf->data[1] = NULL;
        nonleaf->data[2] = NULL;

        if (NULL == nonleaf->parent)
        {
            result = tree_init(in_tree);
            if (SUCCESS != result)
            {
                ERR_MSG("failed to init tree! result=%d.\n", result);
                return result;
            }

            (*in_tree)->child[0] = nonleaf;
            (*in_tree)->child[1] = tree;
            nonleaf->parent = *in_tree;
            tree->parent = *in_tree;
            (*in_tree)->data[0] = tree_min_data(tree);
        }
        else
        {
            pos = tree_last_child_pos(nonleaf->parent);

            for (; (pos >= 0) && (nonleaf->parent->child[pos] != nonleaf); pos--)
            {
                nonleaf->parent->child[pos + 1] = nonleaf->parent->child[pos];
                nonleaf->parent->data[pos] = tree_min_data(nonleaf->parent->child[pos]);
            }

            nonleaf->parent->child[pos + 1] = tree;
            tree->parent = nonleaf->parent;
            nonleaf->parent->data[pos] = tree_min_data(tree);
        }

        nonleaf = nonleaf->parent;
    }

    return SUCCESS;
}

static int tree_insert_adjust(Tree **in_tree, Tree *leaf)
{
    int result = SUCCESS;
    Tree *tree = *in_tree;

    /* num of leaf's data is no more than ORDER, no need adjusting */
    if (tree_child_num(leaf) <= ORDER)
    {
        return SUCCESS;
    }

    result = tree_leaf_split(leaf);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to split leaf! result=%d.\n", result);
        return result;
    }

    result = tree_nonleaf_split(in_tree, leaf->parent);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to split nonleaf! result=%d.\n", result);
        return result;
    }

    return SUCCESS;
}

int tree_insert(Tree **tree, Data *data)
{
    int result = SUCCESS;
    Tree *leaf = NULL;

    if (NULL == tree)
    {
        ERR_MSG("null pointer!\n");
        return NUL_PTR;
    }

    if (NULL == *tree)  /* empty tree */
    {
        return tree_create_with_data(tree, &data, 1);
    }

    result = tree_insert_directly(tree, data, &leaf);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to insert directly!\n");
        return result;
    }

    result = tree_insert_adjust(tree, leaf);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to adjust after insertion!\n");
        return result;
    }

    return SUCCESS;
}

int tree_delete(Tree **tree, Data *data)
{
    return SUCCESS;
}

void tree_clear(Tree **tree)
{
    int pos;

    if ((NULL == tree) || (NULL == *tree))
    {
        return;
    }

    if (tree_is_leaf(*tree))
    {
        for (pos = 0; pos < ORDER; pos++)
        {
            free((*tree)->data[pos]);
        }
    }
    else
    {
        for (pos = 0; pos < ORDER; pos++)
        {
            tree_clear((*tree)->child + pos);
        }
    }

    free(*tree);
    *tree = NULL;
}

static void tree_print_node(Tree *tree)
{
    int pos;

    if (NULL == tree)
    {
        return;
    }

    for (pos = 0; pos < ORDER; pos++)
    {
        if (NULL == tree->data[pos])
        {
            printf("-");
        }
        else
        {
            printf("%d", *(Data *)tree->data[pos]);
        }

        if (pos < ORDER - 1)
        {
            printf(",");
        }
    }

    printf(" ");

}

void tree_levelorder_print_int(Tree *in_tree)
{
    int result;
    int pos;
    Queue *queue = NULL;
    Tree *tree = in_tree;

    if (NULL == tree)
    {
        return;
    }

    result = queue_init(&queue, sizeof(Tree *));
    if (SUCCESS != result)
    {
        ERR_MSG("failed to init queue!\n");
        return;
    }

    result = queue_enqueue(queue, &tree, sizeof(Tree *));
    if (SUCCESS != result)
    {
        ERR_MSG("failed to enqueue tree.\n");
        return;
    }

    while (!queue_is_empty(queue))
    {
        result = queue_dequeue(queue, &tree, sizeof(Tree *));
        if (SUCCESS != result)
        {
            ERR_MSG("failed to dequeue tree.\n");
            queue_clear(&queue);
            return;
        }

        tree_print_node(tree);

        for (pos = 0; pos < ORDER; pos++)
        {
            if (NULL != tree->child[pos])
            {
                result = queue_enqueue(queue, tree->child + pos, sizeof(Tree *));
                if (SUCCESS != result)
                {
                    ERR_MSG("failed to enqueue tree.\n");
                    queue_clear(&queue);
                    return;
                }
            }
        }
    }
}
