#include "utils.h"
#include "two_stack.h"

#define STACK_SIZE  15

enum OPER_CODE
{
    OPER_INIT     = 1,
    OPER_CLEAR    = 2,
    OPER_PUSH     = 3,
    OPER_POP      = 4,
    OPER_TOP      = 5,
    OPER_PRINT    = 6,
    OPER_INVALID
};

void operate_stack(stack *stck, int stck_id, int operation);
void test_stack_init(stack *stck, int size);
void test_stack_push(stack stck, int stck_id);
void test_stack_pop(stack stck, int stck_id);
void test_stack_top(stack stck, int stck_id);

int main()
{
    char go_on = 'y';
    int stck_id = 0;
    int operation = 0;
    int result = SUCCESS;
    stack stck = NULL;

    while (go_on == 'y')
    {
        printf("\nEnter stack's id(0~2): ");
        scanf(" %d", &stck_id);

        printf("Enter operation(1.init, 2. clear 3.push, 4.pop, 5.top, 6.print): ");
        scanf(" %d", &operation);

        if (stck_id < STACK_NUM)
        {
            operate_stack(&stck, stck_id, operation);
        }
        else
        {
            operate_stack(&stck, 0, operation);
            operate_stack(&stck, 1, operation);
        }

        printf("continue? ('y' or 'n'): ");
        scanf(" %c", &go_on);
    }

    stack_clear(stck);

    return 0;
}

void operate_stack(stack *stck, int stck_id, int operation)
{
    if (stck_id >= STACK_NUM)
    {
        printf("The stack id cannot greater than %d!\n", STACK_NUM - 1);
        return;
    }

    if (operation >= OPER_INVALID)
    {
        printf("The operaion code cannot greater than %d\n", OPER_INVALID - 1);
        return;
    }

    switch (operation)
    {
        case OPER_INIT:
        {
            test_stack_init(stck, stck_id);
            break;
        }

        case OPER_CLEAR:
        {
            stack_clear(*stck);
            break;
        }

        case OPER_PUSH:
        {
            test_stack_push(*stck, stck_id);
            break;
        }

        case OPER_POP:
        {
            test_stack_pop(*stck, stck_id);
            break;
        }

        case OPER_TOP:
        {
            test_stack_top(*stck, stck_id);
            break;
        }

        case OPER_PRINT:
        {
            stack_print(*stck, stck_id);
            break;
        }

        default:
            break;
    }
}

void test_stack_init(stack *stck, int stck_id)
{
    int size = 0;
    int result = SUCCESS;

    printf("Enter stack's size: ");
    scanf("%d", &size);

    result = stack_init(stck, size);
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
    }
    else
    {
        printf("init stack successfully.\n");
    }
}

void test_stack_push(stack stck, int stck_id)
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
        result = stack_push(stck, stck_id, arr[pos]);
        if (SUCCESS != result)
        {
            printf("failed to push %d to stack %d!\n", arr[pos], stck_id);
            return;
        }
    }

    printf("push stack successfully.\n");
}

void test_stack_pop(stack stck, int stck_id)
{
    int num = 0;
    int pos = 0;
    int elem = 0;
    int result = SUCCESS;

    printf("Enter elements' number: ");
    scanf("%d", &num);
    printf("Now we pop %d elements from stack %d...\n", num, stck_id);

    for (pos = 0; pos < num; pos++)
    {
        result = stack_pop(stck, stck_id, &elem);
        if (SUCCESS != result)
        {
            printf("failed to pop element from stack %d!\n", stck_id);
            return;
        }

        printf("%d ", elem);
    }

    printf("\n");
}

void test_stack_top(stack stck, int stck_id)
{
    int elem = 0;
    int result = SUCCESS;

    result = stack_top(stck, stck_id, &elem);
    if (SUCCESS != result)
    {
        printf("failed to get the top element of stack %d!\n", stck_id);
    }
    else
    {
        printf("stack %d's top is: %d.\n", stck_id, elem);
    }
}
