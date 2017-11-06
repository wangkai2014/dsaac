#include "utils.h"
#include <ctype.h>
#include "dlist.h"
#include "stack.h"

#define MAX_EXPR_LEN  1000
#define MAX_DIGIT_LEN 10

char priority[128] = {0};
char oper[] = {'+', '-', '*', '/', '^', '(', ')'};

int postfix_to_infix(char *infix_expr, char *post_expr);
int postfix_arr_to_infix_list(struct list *head, char *post_arr);
int infix_list_to_infix_arr(char *arr, struct list *head);
int insert_operand_to_infix_list(struct list *head, char *operand);
int insert_operator_to_infix_list(struct list *head, char operator);
int insert_bracket(struct list *left, struct list *right);
int find_left_sub_expr(struct list *head, struct list *expr, struct list **left, int *prio);
int find_right_sub_expr(struct list *head, struct list *expr, struct list **right, int *prio);
struct list *find_empty_symbol(struct list *head);
int skip_left_bracket(struct list *head, struct list **expr);
int skip_right_bracket(struct list *head, struct list **expr);
void set_priority();
void get_line(char *str);
int read_symbol(char *symbol, char *str, int *pos);
int is_operator(char ch);

int main()
{
    char go_on = 'y';
    char infix_expr[MAX_EXPR_LEN];
    char post_expr[MAX_EXPR_LEN];

    set_priority();

    while (go_on == 'y')
    {
        memset(infix_expr, 0, MAX_EXPR_LEN);
        memset(post_expr, 0, MAX_EXPR_LEN);

        printf("Enter postfix expression:\n");
        get_line(post_expr);

        postfix_to_infix(infix_expr, post_expr);

        printf("The infix expression:\n%s\n", infix_expr);

        printf("Continue?('y' or 'n'): ");
        scanf(" %c", &go_on);
        getchar();  /* consume the Enter key */
    }

    return 0;
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

    while (((ch = getchar()) != EOF) && (ch != '\n') && (pos < MAX_EXPR_LEN-1))
    {
        str[pos++] = ch;
    }

    str[pos] = '\0';
}

int postfix_to_infix(char *infix_expr, char *post_expr)
{
    int result = SUCCESS;
    struct list *head = NULL;

    result = list_init(&head, sizeof(char) * MAX_DIGIT_LEN);
    if (SUCCESS != result)
    {
        printf("failed to init postfix list!\n");
        return result;
    }

    result = postfix_arr_to_infix_list(head, post_expr);
    if (SUCCESS != result)
    {
        printf("failed to transform postfix array to infix list!\n");
        return result;
    }

    result = infix_list_to_infix_arr(infix_expr, head);
    if (SUCCESS != result)
    {
        printf("failed to transform infix list to infix array!\n");
        return result;
    }

    list_clear(head);

    return SUCCESS;
}

int postfix_arr_to_infix_list(struct list *head, char *post_arr)
{
    char symbol[MAX_DIGIT_LEN] = {0};
    int start_pos = 0;
    int result = SUCCESS;

    while (SUCCESS == read_symbol(symbol, post_arr, &start_pos))
    {
        if (isdigit(symbol[0]))
        {
            result = insert_operand_to_infix_list(head, symbol);
            if (SUCCESS != result)
            {
                printf("failed to insert operand %s to infix list.\n", symbol);
                return result;
            }
        }
        else
        {
            result = insert_operator_to_infix_list(head, symbol[0]);
            if (SUCCESS != result)
            {
                printf("failed to insert operator %c to infix list!\n", symbol[0]);
                return result;
            }
        }
    }

    return SUCCESS;
}

int insert_operand_to_infix_list(struct list *head, char *operand)
{
    char empty_symbol[MAX_DIGIT_LEN] = {0};
    int result = SUCCESS;
    struct list *last = list_last(head);

    if ((isdigit(*(char *)(last->data))) || (')' == (*(char *)(last->data))))
    {
        result = list_push_back(head, empty_symbol);
        if (SUCCESS != result)
        {
            printf("failed to push back empty symbol to list!\n");
            return result;
        }
    }

    result = list_push_back(head, operand);
    if (SUCCESS != result)
    {
        printf("failed to push back operand to list!\n");
    }
        
    return result;
}

int insert_operator_to_infix_list(struct list *head, char operator)
{
    int result = SUCCESS;
    int left_prio = 0;
    int right_prio = 0;
    struct list *cur = NULL;
    struct list *left = NULL;
    struct list *right = NULL;

    cur = find_empty_symbol(head);
    if (NULL == cur)
    {
        printf("cannot find empty symbol!\n");
        return NOT_FOUND;
    }

    *(char *)(cur->data) = operator;

    find_left_sub_expr(head, cur, &left, &left_prio);
    if (left_prio < priority[operator])
    {
        result = insert_bracket(left, cur->prev);
    }

    find_right_sub_expr(head, cur, &right, &right_prio);
    if (right_prio < priority[operator])
    {
        result |= insert_bracket(cur->next, right);
    }

    if (SUCCESS != result)
    {
        printf("failed to insert bracket to the list!\n");
    }

    return result;
}

struct list *find_empty_symbol(struct list *head)
{
    struct list *cur = list_last(head);

    while ((head != cur) && (0 != strlen((char *)(cur->data))))
    {
        cur = cur->prev;
    }

    return ((head == cur) ? NULL : cur);
}

int find_left_sub_expr(struct list *head, struct list *expr, struct list **left, int *prio)
{
    char expr_oper = *(char *)(expr->data);
    char cur_oper = 0;
    char min_oper = expr_oper;
    struct list *cur = expr->prev;

    while ((cur != head) && (strlen(cur->data) != 0))
    {
        cur_oper = *(char *)(cur->data);

        if (!is_operator(cur_oper))
        {
            cur = cur->prev;
            continue;
        }

        if (cur_oper == ')')
        {
            skip_left_bracket(head, &cur);
        }
        else if (priority[cur_oper] < priority[expr_oper])
        {
            min_oper = cur_oper;
        }

        cur = cur->prev;
    }

    *prio = priority[min_oper];
    *left = cur->next;

    return SUCCESS;
}

int find_right_sub_expr(struct list *head, struct list *expr, struct list **right, int *prio)
{
    char expr_oper = *(char *)(expr->data);
    char cur_oper = 0;
    char min_oper = expr_oper;
    struct list *cur = expr->next;

    while ((!list_is_end(head, cur)) && (strlen(cur->data) != 0))
    {
        cur_oper = *(char *)(cur->data);

        if (!is_operator(cur_oper))
        {
            cur = cur->next;
            continue;
        }

        if (cur_oper == '(')
        {
            skip_right_bracket(head, &cur);
        }
        else if (priority[cur_oper] < priority[expr_oper])
        {
            min_oper = cur_oper;
        }

        cur = cur->next;
    }

    *prio = priority[min_oper];
    *right = cur->prev;

    return SUCCESS;
}

int skip_left_bracket(struct list *head, struct list **expr)
{
    char oper = *(char *)((*expr)->data);
    char top = 0;
    int result = SUCCESS;
    struct list *cur = (*expr)->prev;
    stack stck = NULL;

    result = stack_init(&stck, sizeof(char));
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
        return result;
    }

    result = stack_push(stck, &oper);
    if (SUCCESS != result)
    {
        printf("failed to push operator to stack!\n");
        return result;
    }

    while ((cur != head) && (!stack_is_empty(stck)))
    {
        oper = *(char *)(cur->data);

        if (oper == '(')
        {
            result = stack_pop(stck, &top);
            if (SUCCESS != result)
            {
                printf("failed to pop closed bracket from stck!\n");
                return result;
            }
        }
        else if (oper == ')')
        {
            result = stack_push(stck, &oper);
            if (SUCCESS != result)
            {
                printf("failed to push closed bracket from stck!\n");
                return result;
            }
        }

        cur = cur->prev;
    }

    return result;
}

int skip_right_bracket(struct list *head, struct list **expr)
{
    char oper = *(char *)((*expr)->data);
    char top = 0;
    int result = SUCCESS;
    struct list *cur = (*expr)->next;
    stack stck = NULL;

    result = stack_init(&stck, sizeof(char));
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
        return result;
    }

    result = stack_push(stck, &oper);
    if (SUCCESS != result)
    {
        printf("failed to push operator to stack!\n");
        return result;
    }

    while ((!list_is_last(head, cur)) && (!stack_is_empty(stck)))
    {
        oper = *(char *)(cur->data);

        if (oper == ')')
        {
            result = stack_pop(stck, &top);
            if (SUCCESS != result)
            {
                printf("failed to pop open bracket from stck!\n");
                return result;
            }
        }
        else if (oper == '(')
        {
            result = stack_push(stck, &oper);
            if (SUCCESS != result)
            {
                printf("failed to push open bracket from stck!\n");
                return result;
            }
        }

        cur = cur->next;
    }

    return result;
}

int insert_bracket(struct list *left, struct list *right)
{
    char open_bracket[]  = "(";
    char close_bracket[] = ")";
    int result;

    result = list_insert(left->prev, open_bracket);
    if (SUCCESS != result)
    {
        printf("failed to insert open bracket to list!\n");
        return result;
    }

    result = list_insert(right, close_bracket);
    if (SUCCESS != result)
    {
        printf("failed to insert close bracket to list!\n");
        return result;
    }

    return SUCCESS;
}

int read_symbol(char *symbol, char *str, int *pos)
{
    int start_pos = *pos;
    int cur_pos = start_pos;

    memset(symbol, 0, MAX_DIGIT_LEN);

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

    while ((str[cur_pos] != ' ') && (str[cur_pos] != '\0') && (cur_pos < MAX_EXPR_LEN-1))
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

int infix_list_to_infix_arr(char *str, struct list *head)
{
    struct list *cur = head->next;
    int start_pos = 0;

    memset(str, 0, MAX_EXPR_LEN);

    while (!list_is_end(head, cur))
    {
        memcpy(str + start_pos, cur->data, strlen(cur->data));
        start_pos += strlen(cur->data);
        str[start_pos++] = ' ';

        cur = cur->next;
    }

    str[--start_pos] = '\0';

    return SUCCESS;
}
