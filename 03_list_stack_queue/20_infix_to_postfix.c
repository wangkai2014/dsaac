#include "utils.h"
#include "stack.h"

#define MAX_EXPR_LEN  1000
#define MAX_DIGIT_LEN 10

char prio[128] = {0};
char oper[] = {'+', '-', '*', '/', '^', '(', ')'};

void set_prio();
void get_line(char *str);
void infix_to_postfix(char *infix_expr, char *post_expr);
int read_symbol(char *str, int *pos, char *operand, char *operator);
int is_operator(char ch);
int cmp_priority(char first, char second);
int proc_operator(stack stck, char in_oper, char *post_expr, int *expr_pos);
int proc_closed_bracket(stack stck, char *post_expr, int *expr_pos);

int main()
{
    char go_on = 'y';
    char infix_expr[MAX_EXPR_LEN];
    char post_expr[MAX_EXPR_LEN];

    set_prio();

    while (go_on == 'y')
    {
        memset(infix_expr, 0, MAX_EXPR_LEN);
        memset(post_expr, 0, MAX_EXPR_LEN);

        printf("Enter infix expression:\n");
        get_line(infix_expr);

        infix_to_postfix(infix_expr, post_expr);

        printf("The postfix expression:\n%s\n", post_expr);

        printf("Continue?('y' or 'n'): ");
        scanf(" %c", &go_on);
        getchar();  /* consume the Enter key */
    }

    return 0;
}

void set_prio()
{
    /* smaller number means lower priority */
    prio['+'] = 2;
    prio['-'] = 2;
    prio['*'] = 3;
    prio['/'] = 3;
    prio['^'] = 4;
    prio['('] = 5;
    prio[')'] = 5;
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

void infix_to_postfix(char *infix_expr, char *post_expr)
{
    int result = SUCCESS;
    int in_pos = 0;
    int out_pos = 0;
    char operator = 0;
    char last_operator = 0;
    char operand[MAX_DIGIT_LEN] = {0};
    stack stck = NULL;

    result = stack_init(&stck, sizeof(char));
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
        return;
    }

    while (SUCCESS == read_symbol(infix_expr, &in_pos, operand, &operator))
    {
        if (operator == 0)  /* the symbol is an operand */
        {
            memcpy(post_expr + out_pos, operand, strlen(operand));
            out_pos += strlen(operand);
            post_expr[out_pos++] = ' ';
        }
        else  /* the symbol is an operator */
        {
            proc_operator(stck, operator, post_expr, &out_pos);
        }
    }

    while (!stack_is_empty(stck))
    {
        result = stack_pop(stck, &operator);
        post_expr[out_pos++] = operator;
        post_expr[out_pos++] = ' ';
    }

    post_expr[out_pos] = '\0';
}

int read_symbol(char *str, int *pos, char *operand, char *operator)
{
    int start_pos = *pos;
    int cur_pos = start_pos;

    if (str[cur_pos] == '\0')
    {
        return FAIL;
    }

    if (is_operator(str[cur_pos]))
    {
        *operator = str[cur_pos];
        *pos = cur_pos + 2;
        return SUCCESS;
    }
    else
    {
        *operator = 0;
    }

    while ((str[cur_pos] != ' ') && (str[cur_pos] != '\0') && (cur_pos < MAX_EXPR_LEN-1))
    {
        cur_pos++;
    }

    memcpy(operand, str + start_pos, cur_pos - start_pos);
    operand[cur_pos - start_pos] = '\0';
    
    if (str[cur_pos] == ' ')
    {
        cur_pos++;
    }

    *pos = cur_pos;

    return SUCCESS;
}

int proc_operator(stack stck, char in_oper, char *post_expr, int *expr_pos)
{
    int pos = *expr_pos;
    int result = SUCCESS;
    char last_oper = 0x7F;

    if (in_oper == ')')
    {
        result = proc_closed_bracket(stck, post_expr, expr_pos);
        return result;
    }

    if ((!stack_is_empty(stck)) &&
        (stack_top(stck, &last_oper) == SUCCESS) &&
        (last_oper == '^') && (in_oper == '^'))
    {
        result = stack_push(stck, &in_oper);
        return result;
    }

    while ((!stack_is_empty(stck)) && 
            (stack_top(stck, &last_oper) == SUCCESS) &&
            (last_oper != '(') &&
            (cmp_priority(in_oper, last_oper) <= 0))
    {
        stack_pop(stck, &last_oper);

        post_expr[pos++] = last_oper;
        post_expr[pos++] = ' ';
    }

    *expr_pos = pos;

    result = stack_push(stck, &in_oper);

    return result;
}

int proc_closed_bracket(stack stck, char *post_expr, int *expr_pos)
{
    int pos = *expr_pos;
    int result = SUCCESS;
    char oper = 0;

    stack_top(stck, &oper);

    while ((!stack_is_empty(stck)) &&
            (stack_pop(stck, &oper) == SUCCESS) &&
            (oper != '('))
    {
        post_expr[pos++] = oper;
        post_expr[pos++] = ' ';
    }
    
    *expr_pos = pos;

    return result;
}

int cmp_priority(char first, char second)
{
    if (prio[first] < prio[second])
    {
        return -1;
    }
    else if (prio[first] > prio[second])
    {
        return 1;
    }
    else
    {
        return 0;
    }
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
