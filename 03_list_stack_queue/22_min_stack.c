#include "utils.h"
#include "min_stack.h"

#define STACK_SIZE  15

enum OPER_CODE
{
    OPER_INIT     = 1,
    OPER_CLEAR    = 2,
    OPER_PUSH     = 3,
    OPER_POP      = 4,
    OPER_TOP      = 5,
    OPER_MIN      = 6,
    OPER_PRINT    = 7,
    OPER_QUIT     = 8,
    OPER_INVALID
};

void operate_stack(stack *stck, int operation);
void test_stack_init(stack *stck);
void test_stack_push(stack stck);
void test_stack_pop(stack stck);
void test_stack_top(stack stck);
void test_stack_min(stack stck);

int main()
{
    int operation = 0;
    int result = SUCCESS;
    stack stck = NULL;

    while (operation < OPER_QUIT)
    {
        printf("\n1.init 2.clear 3.push 4.pop 5.top 6.min 7.print 8.quit\n");
        printf("Enter operation: ");
        scanf("%d", &operation);
        getchar();

        operate_stack(&stck, operation);
    }

    stack_clear(&stck);

    return 0;
}

void operate_stack(stack *stck, int operation)
{
    if (operation >= OPER_INVALID)
    {
        printf("The operaion code cannot greater than %d\n", OPER_INVALID - 1);
        return;
    }

    switch (operation)
    {
        case OPER_INIT:
        {
            test_stack_init(stck);
            break;
        }

        case OPER_CLEAR:
        {
            stack_clear(stck);
            break;
        }

        case OPER_PUSH:
        {
            test_stack_push(*stck);
            break;
        }

        case OPER_POP:
        {
            test_stack_pop(*stck);
            break;
        }

        case OPER_TOP:
        {
            test_stack_top(*stck);
            break;
        }

        case OPER_MIN:
        {
            test_stack_min(*stck);
            break;
        }

        case OPER_PRINT:
        {
            stack_print(*stck);
            break;
        }

        default:
            break;
    }
}

void test_stack_init(stack *stck)
{
    int result = SUCCESS;

    result = stack_init(stck, sizeof(int));
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
    }
    else
    {
        printf("init stack successfully.\n");
    }
}

void test_stack_push(stack stck)
{
    int num = 0;
    int pos = 0;
    int *arr = NULL;
    int result = SUCCESS;

    printf("Enter elements' number: ");
    scanf("%d", &num);

    arr = (int *)malloc(sizeof(int) * num);
    if (NULL == arr)
    {
        printf("failed to malloc memory for arr!\n");
        return;
    }

    printf("Enter elements' value: \n");
    for (pos = 0; pos < num; pos++)
    {
        scanf("%d", arr + pos);
    }

    for (pos = 0; pos < num; pos++)
    {
        result = stack_push(stck, arr + pos);
        if (SUCCESS != result)
        {
            printf("failed to push %d to stack!\n", arr[pos]);
            return;
        }
    }

    printf("push stack successfully.\n");
}

void test_stack_pop(stack stck)
{
    int num = 0;
    int pos = 0;
    int elem = 0;
    int result = SUCCESS;

    printf("Enter elements' number: ");
    scanf("%d", &num);
    printf("Now we pop %d elements from stack...\n", num);

    for (pos = 0; pos < num; pos++)
    {
        result = stack_pop(stck, &elem);
        if (SUCCESS != result)
        {
            printf("failed to pop element from stack!\n");
            return;
        }

        printf("%d ", elem);
    }

    printf("\n");
}

void test_stack_top(stack stck)
{
    int elem = 0;
    int result = SUCCESS;

    result = stack_top(stck, &elem);
    if (SUCCESS != result)
    {
        printf("failed to get the top element of stack!\n");
    }
    else
    {
        printf("stack's top is: %d.\n", elem);
    }
}

void test_stack_min(stack stck)
{
    int elem = 0;
    int result = SUCCESS;

    result = stack_min(stck, &elem);
    if (SUCCESS != result)
    {
        printf("failed to get the smallest element of stack!\n");
    }
    else
    {
        printf("stack's smallest element is: %d.\n", elem);
    }
}
