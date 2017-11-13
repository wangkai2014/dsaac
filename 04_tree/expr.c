#include "utils.h"
#include "stack.h"
#include "binary_tree.h"
#include "expr.h"

char priority[128] = {0};
char oper[] = {'+', '-', '*', '/', '^', '(', ')'};

static int preorder_expr_to_tree(Tree **tree, char *expr)
{
    int result = SUCCESS;

    return result;
}

static int inorder_expr_to_tree(Tree **tree, char *expr)
{
    int result = SUCCESS;

    return result;
}

static int postorder_expr_to_tree(Tree **in_tree, char *expr)
{
    int result = SUCCESS;
    int start = 0;
    char symbol[SYMBOL_LEN];
    Stack *stck = NULL;
    Tree *tree = NULL;
    Tree *left = NULL;
    Tree *right = NULL;

    result = stack_init(&stck, sizeof(Tree *));
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to init stack!\n", __FUNCTION__, __LINE__);
        return result;
    }

    while (SUCCESS == read_symbol(symbol, expr, &start))
    {
        if (is_operator(symbol[0]))
        {
            result = stack_pop(stck, &right, sizeof(Tree *));
            result |= stack_pop(stck, &left, sizeof(Tree *));
            if (SUCCESS != result)
            {
                printf("%s(%d): failed to pop stack!\n", __FUNCTION__, __LINE__);
                stack_clear(&stck);
                return result;
            }
        }
        else
        {
            left = NULL;
            right = NULL;
        }

        result = tree_create(&tree, left, right, symbol, SYMBOL_LEN);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to create tree!\n", __FUNCTION__, __LINE__);
            stack_clear(&stck);
            return result;
        }

        result = stack_push(stck, &tree, sizeof(Tree *));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to push stack!\n", __FUNCTION__, __LINE__);
            stack_clear(&stck);
            return result;
        }
    }

    *in_tree = tree;

    stack_clear(&stck);

    return result;
}

static void print_expr(Tree *tree, char *str, int *start)
{
    int pos = *start;

    if (NULL != tree)
    {
        memcpy(str + pos, tree->data, strlen(tree->data));
        pos += strlen(tree->data);
        str[pos++] = ' ';
        *start = pos;
    }
}

static int tree_to_preorder_expr(char *expr, Tree *in_tree)
{
    int start = 0;

    if ((NULL == expr) || (NULL == in_tree))
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    tree_preorder_visit(in_tree, print_expr, expr, &start);

    return SUCCESS;
}

static int tree_to_inorder_expr(char *expr, Tree *in_tree)
{
    int start = 0;

    if ((NULL == expr) || (NULL == in_tree))
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    tree_inorder_visit(in_tree, print_expr, expr, &start);

    return SUCCESS;
}

static int tree_to_postorder_expr(char *expr, Tree *in_tree)
{
    int start = 0;

    if ((NULL == expr) || (NULL == in_tree))
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    tree_postorder_visit(in_tree, print_expr, expr, &start);

    return SUCCESS;
}

static int expr_to_tree(Tree **tree, char *expr, int order)
{
    int result = SUCCESS;

    switch (order)
    {
        case PRE_ORDER:
        {
            result = preorder_expr_to_tree(tree, expr);
            break;
        }

        case IN_ORDER:
        {
            result = inorder_expr_to_tree(tree, expr);
            break;
        }

        case POST_ORDER:
        {
            result = postorder_expr_to_tree(tree, expr);
            break;
        }

        default:
        {
            result = FAIL;
            break;
        }
    }

    return result;
}

static int tree_to_expr(char *expr, int order, Tree *tree)
{
    int result = SUCCESS;

    switch (order)
    {
        case PRE_ORDER:
        {
            result = tree_to_preorder_expr(expr, tree);
            break;
        }

        case IN_ORDER:
        {
            result = tree_to_inorder_expr(expr, tree);
            break;
        }

        case POST_ORDER:
        {
            result = tree_to_postorder_expr(expr, tree);
            break;
        }

        default:
        {
            result = FAIL;
            break;
        }
    }

    return result;
}

int transform_expr_order(char *dest_expr, int dest_order, char *src_expr, int src_order)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    result = tree_init(&tree, SYMBOL_LEN);
    if (SUCCESS != result)
    {
        printf("failed to init tree in transform_expr_order!\n");
        return result;
    }


    result = expr_to_tree(&tree, src_expr, src_order); 
    if (SUCCESS != result)
    {
        printf("failed to transform expr to tree! src_expr=%s, src_order=%d.\n", src_expr, src_order);
        tree_clear(&tree);
        return result;
    }

    result = tree_to_expr(dest_expr, dest_order, tree);
    if (SUCCESS != result)
    {
        printf("failed to transform tree to expr! src_expr=%s, src_order=%d, dest_order=%d.\n", src_expr, src_order, dest_order);
    }

    tree_clear(&tree);

    return result;
}

void set_priority()
{
    /* smaller number means lower priorityrity */
    priority['+'] = 2;
    priority['-'] = 2;
    priority['*'] = 3;
    priority['/'] = 3;
    priority['^'] = 4;
    priority['('] = 5;
    priority[')'] = 5;
}

void get_line(char *str)
{
    char ch;
    int pos = 0;

    while (((ch = getchar()) != EOF) && (ch != '\n') && (pos < EXPR_LEN-1))
    {
        str[pos++] = ch;
    }

    str[pos] = '\0';
}

int read_symbol(char *symbol, char *str, int *pos)
{
    int start_pos = *pos;
    int cur_pos = start_pos;

    memset(symbol, 0, SYMBOL_LEN);

    if (str[cur_pos] == '\0')
    {
        return FAIL;
    }

    if (is_operator(str[cur_pos]))
    {
        symbol[0] = str[cur_pos];
        *pos = cur_pos + 2;
        return SUCCESS;
    }

    while ((str[cur_pos] != ' ') && (str[cur_pos] != '\0') && (cur_pos < EXPR_LEN-1))
    {
        cur_pos++;
    }

    memcpy(symbol, str + start_pos, cur_pos - start_pos);
    
    if (str[cur_pos] == ' ')
    {
        cur_pos++;
    }

    *pos = cur_pos;

    return SUCCESS;
}

int is_operator(char ch)
{
    int num = sizeof(oper) / sizeof(char);
    int pos;

    for (pos = 0; pos < num; pos++)
    {
        if (ch == oper[pos])
        {
            return TRUE;
        }
    }

    return FALSE;
}

int cmp_priority(char first, char second)
{
    if (priority[first] < priority[second])
    {
        return -1;
    }
    else if (priority[first] > priority[second])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
