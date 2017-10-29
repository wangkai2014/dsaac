#include "utils.h"
#include <math.h>
#include <ctype.h>
#include "stack.h"

#define MAX_EXP_LEN 1000

void get_line(char *str);
void evaluate_postfix_expression(char *express);
void calc_expression(double first, double second, char operator, double *answer);
int read_symbol(char *express, int *start_pos, char *operator, double *operand);

int main()
{
    char go_on = 'y';
    char express[MAX_EXP_LEN];

    while (go_on == 'y')
    {
        memset(express, 0, MAX_EXP_LEN);

        printf("Enter a postfix expression:\n");
        get_line(express);

        evaluate_postfix_expression(express);

        printf("\nContinue?('y' or 'n'): ");
        scanf(" %c", &go_on);
        getchar();
    }

    return 0;
}

void get_line(char *str)
{
    char ch = getchar();
    int pos = 0;

    while ((ch != EOF) && (ch != '\n') && (pos < MAX_EXP_LEN))
    {
        str[pos++] = ch;
        ch = getchar();
    }
}

void evaluate_postfix_expression(char *express)
{
    int result = SUCCESS;
    int start_pos = 0;
    char operator = 0;
    double operand = 0;
    double first = 0;
    double second = 0;
    double answer = 0;
    
    stack stck = NULL;

    result = stack_init(&stck, sizeof(double)); 
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
        return;
    }

    while (SUCCESS == read_symbol(express, &start_pos, &operator, &operand))
    {
        if (operator != 0)
        {
            result = stack_pop(stck, &first);
            result |= stack_pop(stck, &second);
            if (SUCCESS != result)
            {
                printf("failed to pop the stack![%d]\n", result);
                return;
            }

            calc_expression(first, second, operator, &answer);

            result = stack_push(stck, &answer);
            if (SUCCESS != result)
            {
                printf("failed to push the answer[%f] to the stack!\n", answer);
                return;
            }
        }
        else
        {
            result = stack_push(stck, &operand);
            if (SUCCESS != result)
            {
                printf("failed to push the operand[%f] to the stack!\n", operand);
                return;
            }
        }
    }

    printf("the result is %.2f.\n", answer);

    stack_pop(stck, &result);

    if (!stack_is_empty(stck))
    {
        printf("error! some of the postfix expression cannot be evaluate!\n");
        stack_clear(stck);
    }
}

int is_operator(char ch)
{
    char operators[] = {'+', '-', '*', '/', '^'};
    int oper_num = sizeof(operators) / sizeof(char);
    int pos;

    for (pos = 0; pos < oper_num; pos++)
    {
        if (ch == operators[pos])
        {
            return TRUE;
        }
    }

    return FALSE;
}

int read_symbol(char *express, int *start_pos, char *operator, double *operand)
{
    int pos = *start_pos;
    double num = 0;
    double base = 0.1;

    *operator = 0;

    if (express[pos] == ' ')
    {
        pos++;
        *start_pos = pos;
    }

    if (is_operator(express[pos]))
    {
        *operator = express[pos];
        *start_pos = pos + 1;
        return SUCCESS;
    }

    while (isdigit(express[pos]))
    {
        num = express[pos] - '0' + num * 10;
        pos++;
    }

    if (express[pos] == '.')
    {
        while (isdigit(express[++pos]))
        {
            num += (express[pos] - '0') * base;
            base *= 0.1;
        }
    }

    if ((*start_pos) == pos)
    {
        return FAIL;
    }
    else
    {
        *operand = num;
        *start_pos = pos;
        return SUCCESS;
    }
}

void calc_expression(double first, double second, char operator, double *answer)
{
    *answer = 0;

    switch (operator)
    {
        case '+':
        {
            *answer = first + second;
            break;
        }

        case '-':
        {
            *answer = first - second;
            break;
        }

        case '*':
        {
            *answer = first * second;
            break;
        }

        case '/':
        {
            *answer = first / second;
            break;
        }

        case '^':
        {
            //*answer = pow(first, second);
            break;
        }

        default:
        {
            break;
        }
    }
}
