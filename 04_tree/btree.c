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

    if (tree_is_leaf(tree))
    {
        for (pos = 0; tree->data[pos] != NULL; pos++);
    }
    else
    {
        for (pos = 0; tree->child[pos] != NULL; pos++);
    }

    return pos;
}

static Data *tree_min_data(Tree *tree)
{
    if (NULL == tree)
    {
        return NULL;
    }

    while (!tree_is_leaf(tree))
    {
        tree = tree->child[0];
    }

    return tree->data[0];
}

static void tree_refresh_data(Tree *tree)
{
    int pos;

    if ((NULL == tree) || (NULL == tree->child[0]))
    {
        return;
    }

    for (pos = 0; pos < ORDER; pos++)
    {
        tree_refresh_data(tree->child[pos]);
    }

    for (pos = 0; pos < ORDER - 1; pos++)
    {
        tree->data[pos] = tree_min_data(tree->child[pos + 1]);
    }
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

static int tree_find_unfill_sibl(Tree *tree)
{
    int pos;
    int child_num;

    if ((NULL == tree) || (NULL == tree->child[0]))
    {
        return ORDER;
    }

    /* we get priority to the sibling at pos 1, since it simplify the problem */
    if (tree_child_num(tree->child[1]) < ORDER)
    {
        return 1;
    }

    child_num = tree_child_num(tree);

    for (pos = 0; pos < child_num; pos++)
    {
        if (tree_child_num(tree->child[pos]) < ORDER)
        {
            return pos;
        }
    }

    return ORDER;
}

static void tree_adopt_data_to_sibl(Tree **tree, Tree *leaf, int sibl_pos)
{
    int pos;
    int leaf_pos;
    Tree *sibl;
    Tree *midl;

    /* get position of leaf */
    for (leaf_pos = 0; leaf->parent->child[leaf_pos] != leaf; leaf_pos++);

    sibl = leaf->parent->child[sibl_pos];
    midl = leaf->parent->child[1];

    if (leaf_pos - sibl_pos == -2)
    {
        for (pos = ORDER - 1; pos > 0; pos--)
        {
            sibl->data[pos] = sibl->data[pos - 1];
        }

        sibl->data[0] = midl->data[ORDER - 1];
        midl->data[ORDER - 1] = NULL;
        sibl_pos = 1;
        sibl = midl;
    }
    else if (leaf_pos - sibl_pos == 2)
    {
        sibl->data[ORDER - 1] = midl->data[0];

        for (pos = 0; pos < ORDER; pos++)
        {
            midl->data[pos] = midl->data[pos + 1];
        }

        sibl_pos = 1;
        sibl = midl;
    }

    if (leaf_pos - sibl_pos == -1)
    {
        for (pos = ORDER - 1; pos > 0; pos--)
        {
            sibl->data[pos] = sibl->data[pos - 1];
        }

        sibl->data[0] = leaf->data[ORDER];
    }
    else if (leaf_pos - sibl_pos == 1)
    {
        sibl->data[ORDER - 1] = leaf->data[0];

        for (pos = 0; pos < ORDER; pos++)
        {
            leaf->data[pos] = leaf->data[pos + 1];
        }
    }

    leaf->data[ORDER] = NULL;

    tree_refresh_data(*tree);
}

static int tree_insert_adjust(Tree **in_tree, Tree *leaf)
{
    int result = SUCCESS;
    int sibl_pos;
    Tree *tree = *in_tree;

    /* num of leaf's data is no more than ORDER, no need adjusting */
    if (tree_child_num(leaf) <= ORDER)
    {
        return SUCCESS;
    }

    if ((sibl_pos = tree_find_unfill_sibl(leaf->parent)) != ORDER)
    {
        tree_adopt_data_to_sibl(in_tree, leaf, sibl_pos);
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

    if ((NULL == tree) || (NULL == data))
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

static int tree_delete_directly(Tree **in_tree, Data *data, Tree **target)
{
    int result;
    int pos;
    Tree *tree = *in_tree;

    /* find the position of the target data */
    while (!tree_is_leaf(tree))
    {
        pos = 0;
        while ((tree->data[pos] != NULL) &&
               (cmp_data(tree->data[pos], data) <= 0))
        {
            pos++;
        }

        tree = tree->child[pos];
    }

    pos = 0;
    while ((tree->data[pos] != NULL) &&
           (cmp_data(tree->data[pos], data) != 0))
    {
        pos++;
    }

    if (tree->data[pos] == NULL)
    {
        ERR_MSG("not found!\n");
        return NOT_FOUND;
    }

    free(tree->data[pos]);

    for (; tree->data[pos] != NULL; pos++)
    {
        tree->data[pos] = tree->data[pos + 1];
    }

    *target = tree;

    return SUCCESS;
}

static void tree_merge_two_leaf(Tree *leaf, Tree *sibl, int leaf_pos)
{
    int pos;

    if (leaf_pos == 0)
    {
        for (pos = 1; pos < ORDER; pos++)
        {
            leaf->data[pos] = sibl->data[pos - 1];
        }
    }
    else
    {
        leaf->data[ORDER - 1] = leaf->data[0];

        for (pos = 0; pos < ORDER - 1; pos++)
        {
            leaf->data[pos] = sibl->data[pos];
        }
    }

    /* get sibling's position */
    pos = (leaf_pos == 0)? 1 : (leaf_pos - 1);

    for (; pos < ORDER; pos++)
    {
        sibl->parent->child[pos] = sibl->parent->child[pos + 1];
    }

    free(sibl);
}

static void tree_steal_from_sibl_leaf(Tree *leaf, Tree *sibl, int pos)
{
    if (pos == 0)
    {
        leaf->data[1] = sibl->data[0];

        for (pos = 0; pos < ORDER; pos++)
        {
            sibl->data[pos] = sibl->data[pos + 1];
        }
    }
    else
    {
        leaf->data[1] = leaf->data[0];
        leaf->data[0] = sibl->data[ORDER - 1];
        sibl->data[ORDER - 1] = NULL;
    }
}

/* adjust after delete a date of some leaf:
 * 1. if the leaf's sibling have 2 datas, then merge two leaf 
 * 2. if the leaf's sibling have 3 datas, then steal 1 data from him */
static int tree_delete_leaf_adjust(Tree **in_tree, Tree *leaf)
{
    int pos;
    Tree *sibl;

    /* find out the position of the leaf among its sibling */
    for (pos = 0; leaf->parent->child[pos] != leaf; pos++);

    sibl = (pos == 0)? leaf->parent->child[1] : leaf->parent->child[pos - 1];

    if (tree_child_num(sibl) < ORDER)
    {
        tree_merge_two_leaf(leaf, sibl, pos);
    }
    else
    {
        tree_steal_from_sibl_leaf(leaf, sibl, pos);
    }

    return SUCCESS;
}

static void tree_merge_two_nonleaf(Tree *nonleaf, Tree *sibl, int nonleaf_pos)
{
    int pos;

    if (nonleaf_pos == 0)
    {
        for (pos = 1; pos < ORDER; pos++)
        {
            nonleaf->child[pos] = sibl->child[pos - 1];
            nonleaf->child[pos]->parent = nonleaf;
        }
    }
    else
    {
        nonleaf->child[ORDER - 1] = nonleaf->child[0];

        for (pos = 0; pos < ORDER - 1; pos++)
        {
            nonleaf->child[pos] = sibl->child[pos];
            nonleaf->child[pos]->parent = nonleaf;
        }
    }

    /* get sibling's position */
    pos = (nonleaf_pos == 0)? 1 : (nonleaf_pos - 1);

    for (; pos < ORDER; pos++)
    {
        sibl->parent->child[pos] = sibl->parent->child[pos + 1];
    }

    free(sibl);
}

static void tree_steal_from_sibl_nonleaf(Tree *nonleaf, Tree *sibl, int pos)
{
    if (pos == 0)
    {
        nonleaf->child[1] = sibl->child[0];
        nonleaf->child[1]->parent = nonleaf;

        for (pos = 0; pos < ORDER; pos++)
        {
            sibl->child[pos] = sibl->child[pos + 1];
        }
    }
    else
    {
        nonleaf->child[1] = nonleaf->child[0];
        nonleaf->child[0] = sibl->child[ORDER - 1];
        nonleaf->child[0]->parent = nonleaf;
        sibl->child[ORDER - 1] = NULL;
    }
}

static int tree_delete_nonleaf_adjust(Tree **in_tree, Tree *nonleaf)
{
    int pos;
    Tree *sibl;

    while ((NULL != nonleaf->parent) && (tree_child_num(nonleaf) == 1))
    {
        for (pos = 0; nonleaf->parent->child[pos] != nonleaf; pos++);

        sibl = (pos == 0)? nonleaf->parent->child[1] : nonleaf->parent->child[pos - 1];

        if (tree_child_num(sibl) < ORDER)
        {
            tree_merge_two_nonleaf(nonleaf, sibl, pos);
        }
        else
        {
            tree_steal_from_sibl_nonleaf(nonleaf, sibl, pos);
        }

        nonleaf = nonleaf->parent;
    }

    if ((NULL == nonleaf->parent) && (tree_child_num(nonleaf) == 1))
    {
        *in_tree = nonleaf->child[0];
        nonleaf->child[0]->parent = NULL;

        free(nonleaf);
    }

    return SUCCESS;
}

static int tree_delete_adjust(Tree **in_tree, Tree *leaf)
{
    int result;

    /* child's num satifies b-tree's properties, only need to refresh data */
    if ((NULL == leaf->parent) || (tree_child_num(leaf) > 1))
    {
        tree_refresh_data(*in_tree);

        return SUCCESS;
    }

    result = tree_delete_leaf_adjust(in_tree, leaf);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to adjust leaf after deletion!\n");
        return result;
    }

    result = tree_delete_nonleaf_adjust(in_tree, leaf->parent);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to adjust nonleaf after deletion!\n");
        return result;
    }

    tree_refresh_data(*in_tree);

    return SUCCESS;
}

int tree_delete(Tree **tree, Data *data)
{
    int result = SUCCESS;
    Tree *leaf = NULL;

    if ((NULL == tree) || (NULL == *tree) || (NULL == data))
    {
        ERR_MSG("null pointer!\n");
        return NUL_PTR;
    }

    result = tree_delete_directly(tree, data, &leaf);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to delete directly!\n");
        return result;
    }

    result = tree_delete_adjust(tree, leaf);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to adjust after deletion!\n");
        return result;
    }

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
