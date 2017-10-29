#include "utils.h"
#include "stack.h"

#define MAX_LEN     1000
#define SYMBOL_LEN  6
#define INVALID_POS -1
#define LEFT   1
#define RIGHT  2

int read_symbol(char *str, int start_pos, char *symbol, int *dir_flag);
int is_balance_symbol(char *left_symbol, char *right_symbol);
void check_balance_symbol(char *str);

int main()
{
    char go_on = 'y';
    char str[MAX_LEN];

    while (go_on == 'y')
    {
        memset(str, 0, MAX_LEN);

        printf("Enter string:\n");
        scanf("%s", str);

        check_balance_symbol(str);

        printf("\ncontinue? ('y' or 'n'): ");
        scanf(" %c", &go_on);
    }

    return 0;
}

/*
 * the algorithm is as following:
 * 1. read a symbol
 * 2. if symbol is left_bracket, push it to the stack
 * 3. if symbol is right_bracket, pop a symbol from the stack, and check balance
 * 4. at the end, if the stack is empty, then the check passed ,otherwise failed
*/
void check_balance_symbol(char *str)
{
    stack stck = NULL;
    char left_symbol[SYMBOL_LEN] = {0};
    char cur_symbol[SYMBOL_LEN] = {0};
    int result = SUCCESS;
    int start_pos = 0;
    int symbol_pos = INVALID_POS;
    int dir_flag = 0;  /* the direction of the symbol, 1: left, 2: right */
    
    result = stack_init(&stck, sizeof(char) * SYMBOL_LEN);
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
        return;
    }

    while ((symbol_pos = read_symbol(str, start_pos, cur_symbol, &dir_flag)) != INVALID_POS)
    {
        if (LEFT == dir_flag)
        {
            result = stack_push(stck, cur_symbol); 
            if (SUCCESS != result)
            {
                printf("failed to push stack!\n");
                return;
            }
        }
        else
        {
            result = stack_pop(stck, left_symbol);
            if (SUCCESS != result)
            {
                printf("failed to pop stack!\n");
                return;
            }

            if (!is_balance_symbol(left_symbol, cur_symbol))
            {
                printf("failed! the right symbol \"%s\" does not match the left symbol \"%s\"!\n", cur_symbol, left_symbol);
                return;
            }
        }
    
        start_pos = symbol_pos + strlen(cur_symbol);
    }

    if (stack_is_empty(stck))
    {
        printf("pass the check for balancing symbols!\n");
    }
    else
    {
        stack_top(stck, left_symbol);
        printf("failed! the left symbol \"%s\" doesn't meet right symbol!", left_symbol);
    }
}

int read_symbol(char *str, int start_pos, char *symbol, int *dir_flag)
{
    char *brackets[] = {"(", "[", "{", "/*", "begin", 
                        ")", "]", "}", "*/", "end"};
    char sub_str[SYMBOL_LEN] = {0};
    int bracket_num = sizeof(brackets) / sizeof(char *);
    int bracket_len = 0;
    int index = 0;
    int pos = start_pos;

    memset(symbol, 0, SYMBOL_LEN);

    while (str[pos] != '\0')
    {
        for (index = 0; index < bracket_num; index++)
        {
            bracket_len = strlen(brackets[index]);

            if (strlen(str + pos) < strlen(brackets[index]))
            {
                continue;
            }

            memcpy(sub_str, str + pos, bracket_len);
            sub_str[bracket_len] = '\0';

            if (0 == strcmp(sub_str, brackets[index]))
            {
                memcpy(symbol, brackets[index], strlen(brackets[index]));

                *dir_flag = ((index < bracket_num/2) ? LEFT : RIGHT);

                return pos;
            }
        }

        pos++;
    }

    return INVALID_POS;
}

int is_balance_symbol(char *left_symbol, char *right_symbol)
{
    char *left_bracket[] = {"(", "[", "{", "/*", "begin"};
    char *right_bracket[] = {")", "]", "}", "*/", "end"};
    int bracket_num = sizeof(left_bracket) / sizeof(char *);
    int pos;

    for (pos = 0; pos < bracket_num; pos++)
    {
        if (0 == strcmp(left_symbol, left_bracket[pos]))
        {
            return ((0 == strcmp(right_symbol, right_bracket[pos])) ? TRUE : FALSE);
        }
    }

    return FALSE;
}
