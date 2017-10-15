#include "utils.h"
#include "arithmetic.h"

static int get_operation(int *operation);
static int get_operand(char *first_operand, char *second_operand, int operation);
static int calculate(char *first_operand, char *second_operand, char *answer, int operation);
static int print_answer(char *first_operand, char *second_operand, char *answer, int operation);

int main()
{
    char go_on = 'y';
    int operation = 0;
    int result = SUCCESS;
    char *first_operand = NULL;
    char *second_operand = NULL;
    char *answer = NULL;

    first_operand = (char *)malloc(sizeof(char) * MAX_DIGIT_NUM);
    second_operand = (char *)malloc(sizeof(char) * MAX_DIGIT_NUM);
    answer = (char *)malloc(sizeof(char) * MAX_DIGIT_NUM);
    if ((NULL == first_operand) || (NULL == second_operand) || (NULL == answer))
    {
        print_error("failed to malloc memory!");
        return 0;
    }

    while (('y' == go_on) || ('Y' == go_on))
    {
        result = get_operation(&operation);
        if (SUCCESS != result)
        {
            print_error("failed to get operation!");
            continue;
        }
        
        result = get_operand(first_operand, second_operand, operation);
        if (SUCCESS != result)
        {
            print_error("failed to get operand!");
            continue;
        }

        result = calculate(first_operand, second_operand, answer, operation);
        if (SUCCESS != result)
        {
            print_error("failed to calculate the operation!");
            continue;
        }

        print_answer(first_operand, second_operand, answer, operation);

        printf("whether to continue(y or n)? ");
        scanf(" %c", &go_on);
    }
    
    free(first_operand);
    free(second_operand);
    free(answer);

    return 0;
}

static int get_operation(int *operation)
{
    if (NULL == operation)
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    printf("\n****************************** Input Operation *****************************\n");
    printf("1. Addition 2. Subtraction 3. Multiplication 4. Division 5. Exponentiation\n");
    printf("Enter an arithmetic operation: ");
    
    scanf("%d", operation);

    return SUCCESS;
}

static int get_operand(char *first_operand, char *second_operand, int operation)
{
    if ((NULL == first_operand) || (NULL == second_operand))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    if (operation >= MAX_OPERATION)
    {
        print_error("invalid operation!");
        return OUT_OF_RANGE;
    }

    memset(first_operand, 0, MAX_DIGIT_NUM);
    memset(second_operand, 0, MAX_DIGIT_NUM);

    printf("\n******************************* Input Operand ******************************\n");
    if (operation == EXPONENTIATION)
    {
        printf("Enter base:     ");
        scanf("%s", first_operand);

        printf("Enter exponent: ");
        scanf("%s", second_operand);
    }
    else
    {
        printf("Enter first operand:  ");
        scanf("%s", first_operand);

        printf("Enter second operand: ");
        scanf("%s", second_operand);
    }

    return SUCCESS;
}

static int calculate(char *first_operand, char *second_operand, char *answer, int operation)
{
    int result = SUCCESS;

    if ((NULL == first_operand) || (NULL == second_operand) || (NULL == answer))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    switch (operation)
    {
        case ADDITION:
        {
            result = add(first_operand, second_operand, answer);
            break;
        }

        case SUBTRACTION:
        {
            result = subtract(first_operand, second_operand, answer);
            break;
        }

        case MULTIPLICATION:
        {
            result = multiply(first_operand, second_operand, answer);
            break;
        }

        case DIVISION:
        {
            result = divide(first_operand, second_operand, answer);
            break;
        }

        case EXPONENTIATION:
        {
            result = exponent(first_operand, second_operand, answer);
            break;
        }

        default:
        {
            result = OUT_OF_RANGE;
            break;
        }
    }

    if (SUCCESS != result)
    {
        print_error("failed to execute the operation!");
    }

    return result;
}

static int print_answer(char *first_operand, char *second_operand, char *answer, int operation)
{
    char opt[6] = {' ', '+', '-', '*', '/','^'};

    if ((NULL == first_operand) || (NULL == second_operand) || (NULL == answer))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    if (operation >= MAX_OPERATION)
    {
        print_error("invalid operation!");
        return OUT_OF_RANGE;
    }

    printf("\n******************************* Output Result ******************************\n");
    printf("%s %c %s = \n%s\n\n", first_operand, opt[operation], second_operand, answer);

    return SUCCESS;
}
