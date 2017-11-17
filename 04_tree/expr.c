#include "utils.h"
#include "stack.h"
#include "binary_tree.h"
#include "expr.h"

typedef void (*Visit)(Tree *, char *, int *);

char g_priority[128] = {0};
char g_operator[] = {'+', '-', '*', '/', '^', '(', ')'};

void set_priority()
{
    /* smaller number means lower g_priorityrity */
    g_priority['+'] = 2;
    g_priority['-'] = 2;
    g_priority['*'] = 3;
    g_priority['/'] = 3;
    g_priority['^'] = 4;
    g_priority['('] = 5;
    g_priority[')'] = 5;
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
    int num = sizeof(g_operator) / sizeof(char);
    int pos;

    for (pos = 0; pos < num; pos++)
    {
        if (ch == g_operator[pos])
        {
            return TRUE;
        }
    }

    return FALSE;
}

int cmp_priority(char first, char second)
{
    if (g_priority[first] < g_priority[second])
    {
        return -1;
    }
    else if (g_priority[first] > g_priority[second])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static int preorder_expr_to_tree(Tree **tree, char *expr)
{
    int result = SUCCESS;

    return result;
}

static int proc_bracket_of_inorder_expr(Stack *expr_stck, Stack *oper_stck)
{
    int result = SUCCESS;
    char top_oper[SYMBOL_LEN];
    Tree *tree = NULL;
    Tree *left = NULL;
    Tree *right = NULL;

    while ((!stack_is_empty(oper_stck)) &&
           (SUCCESS == stack_top(oper_stck, top_oper, sizeof(char))) &&
           ('(' != top_oper[0]))
    {
        result = stack_pop(oper_stck, top_oper, sizeof(char));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to pop oper_stck!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = stack_pop(expr_stck, &right, sizeof(Tree *));
        result = stack_pop(expr_stck, &left, sizeof(Tree *));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to pop expr_stck!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = tree_create(&tree, left, right, top_oper, SYMBOL_LEN);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = stack_push(expr_stck, &tree, sizeof(Tree *));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to push expr_stck!\n", __FUNCTION__, __LINE__);
            return result;
        }
    }

    result = stack_pop(oper_stck, top_oper, SYMBOL_LEN);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to pop oper_stck!\n", __FUNCTION__, __LINE__);
    }

    return result;
}

static int proc_operator_of_inorder_expr(Stack *expr_stck, Stack *oper_stck, char oper)
{
    int result = SUCCESS;
    char top_oper[SYMBOL_LEN];
    Tree *tree = NULL;
    Tree *left = NULL;
    Tree *right = NULL;

    while ((!stack_is_empty(oper_stck)) &&
           (SUCCESS == stack_top(oper_stck, top_oper, sizeof(char))) &&
           (cmp_priority(top_oper[0], oper) >= 0))
    {
        result = stack_pop(oper_stck, top_oper, sizeof(char));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to pop oper_stck!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = stack_pop(expr_stck, &right, sizeof(Tree *));
        result = stack_pop(expr_stck, &left, sizeof(Tree *));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to pop expr_stck!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = tree_create(&tree, left, right, top_oper, SYMBOL_LEN);
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to init tree!\n", __FUNCTION__, __LINE__);
            return result;
        }

        result = stack_push(expr_stck, &tree, sizeof(Tree *));
        if (SUCCESS != result)
        {
            printf("%s(%d): failed to push expr_stck!\n", __FUNCTION__, __LINE__);
            return result;
        }
    }

    memset(top_oper, 0, SYMBOL_LEN);
    top_oper[0] = oper;

    result = stack_push(oper_stck, top_oper, SYMBOL_LEN);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to push oper_stck!\n", __FUNCTION__, __LINE__);
    }

    return result;
}

static int proc_operand_of_inorder_expr(Stack *expr_stck, char *symbol)
{
    int result = SUCCESS;
    Tree *tree = NULL;

    result = tree_create(&tree, NULL, NULL, symbol, SYMBOL_LEN);
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to create tree!\n", __FUNCTION__, __LINE__);
        return result;
    }

    result = stack_push(expr_stck, &tree, sizeof(Tree *));
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to push expr_stck!\n", __FUNCTION__, __LINE__);
    }

    return result;
}

static int inorder_expr_to_tree(Tree **tree, char *expr)
{
    int result = SUCCESS;
    int start = 0;
    char symbol[SYMBOL_LEN];
    Stack *expr_stck = NULL;  /* stack of expression trees */
    Stack *oper_stck = NULL;  /* stack of operator trees */

    result = stack_init(&expr_stck, sizeof(Tree *));
    result |= stack_init(&oper_stck, sizeof(char));
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to init stack!\n", __FUNCTION__, __LINE__);
        return result;
    }

    while (SUCCESS == read_symbol(symbol, expr, &start))
    {
        if (')' == symbol[0])
        {
            result = proc_bracket_of_inorder_expr(expr_stck, oper_stck);
        }
        else if (is_operator(symbol[0]))
        {
            result = proc_operator_of_inorder_expr(expr_stck, oper_stck, symbol[0]);
        }
        else
        {
            result = proc_operand_of_inorder_expr(expr_stck, symbol);
        }

        if (SUCCESS != result)
        {
            printf("%s(%d): failed to proc symbol %s! result=%d!\n", __FUNCTION__, __LINE__, symbol, result);
            return result;
        }
    }

    /* use brank character to pop all the operators on the oper_stck */
    result = proc_operator_of_inorder_expr(expr_stck, oper_stck, ' ');
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to proc operator ^!\n", __FUNCTION__, __LINE__);
        return result;
    }

    result = stack_pop(expr_stck, tree, sizeof(Tree*));
    if (SUCCESS != result)
    {
        printf("%s(%d): failed to pop expr_stck!\n", __FUNCTION__, __LINE__);
    }

    stack_clear(&expr_stck);
    stack_clear(&oper_stck);

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

static void print_expr_tree(Tree *tree, char *str, int *start)
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

static void preorder_visit_expr_tree(Tree *tree, Visit visit, char *str, int *start)
{
    if ((NULL == tree) || (NULL == visit))
    {
        return;
    }

    (*visit)(tree, str, start);

    preorder_visit_expr_tree(tree->left, visit, str, start);

    preorder_visit_expr_tree(tree->right, visit, str, start);
}

static void inorder_visit_expr_tree(Tree *tree, Visit visit, char *str, int *start)
{
    if ((NULL == tree) || (NULL == visit))
    {
        return;
    }

    if ((NULL != tree->left) && 
        (is_operator(*(char*)tree->left->data) &&
        (cmp_priority(*(char*)(tree->data), *(char*)(tree->left->data)) > 0)))
    {
        str[(*start)++] = '(';
        str[(*start)++] = ' ';

        inorder_visit_expr_tree(tree->left, visit, str, start);

        str[(*start)++] = ')';
        str[(*start)++] = ' ';

    }
    else
    {
        inorder_visit_expr_tree(tree->left, visit, str, start);
    }

    (*visit)(tree, str, start);

    if ((NULL != tree->right) && 
        (is_operator(*(char*)tree->right->data) &&
        (cmp_priority(*(char*)(tree->data), *(char*)(tree->right->data)) > 0)))
    {
        str[(*start)++] = '(';
        str[(*start)++] = ' ';

        inorder_visit_expr_tree(tree->right, visit, str, start);

        str[(*start)++] = ')';
        str[(*start)++] = ' ';
    }
    else
    {
        inorder_visit_expr_tree(tree->right, visit, str, start);
    }
}

static void postorder_visit_expr_tree(Tree *tree, Visit visit, char *str, int *start)
{
    if ((NULL == tree) || (NULL == visit))
    {
        return;
    }

    postorder_visit_expr_tree(tree->left, visit, str, start);

    postorder_visit_expr_tree(tree->right, visit, str, start);

    (*visit)(tree, str, start);
}

static int tree_to_preorder_expr(char *expr, Tree *in_tree)
{
    int start = 0;

    if ((NULL == expr) || (NULL == in_tree))
    {
        printf("%s(%d): null pointer!\n", __FUNCTION__, __LINE__);
        return NUL_PTR;
    }

    preorder_visit_expr_tree(in_tree, print_expr_tree, expr, &start);

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

    inorder_visit_expr_tree(in_tree, print_expr_tree, expr, &start);

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

    postorder_visit_expr_tree(in_tree, print_expr_tree, expr, &start);

    return SUCCESS;
}

static int expr_to_tree(Tree **tree, char *expr, int order)
{
    int result = SUCCESS;

    set_priority();

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
