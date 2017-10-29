#include "utils.h"
#include "stack.h"

#define ARRAY_SIZE  10

int main()
{
    int result = SUCCESS;
    int pos = 0;
    int data = 0;
    int arr[ARRAY_SIZE];
    stack stck = NULL;

    printf("\nNow we test stack init...\n");

    result = stack_init(&stck, sizeof(int));
    if (SUCCESS != result)
    {
        printf("failed to init stack!\n");
        return 0;
    }
    else
    {
        printf("succeed to init stack!\n");
    }

    for (pos = 0; pos < ARRAY_SIZE; pos++)
    {
        arr[pos] = pos * (pos + 3);
    }

    printf("\nNow we test stack push and top...\n");

    for (pos = 0; pos < ARRAY_SIZE; pos++)
    {
        result = stack_push(stck, arr + pos);
        if (SUCCESS != result)
        {
            printf("failed to push element to stack!\n");
            return 0;
        }

        result = stack_top(stck, &data);
        if (SUCCESS != result)
        {
            printf("failed to get the top of stack!\n");
            return 0;
        }

        printf("%d ", data);
    }

    printf("\n\nNow we test stack pop...\n");

    for (pos = 0; pos < ARRAY_SIZE; pos++)
    {
        result = stack_pop(stck, &data);
        if (SUCCESS != result)
        {
            printf("failed to pop element from stack!\n");
            return 0;
        }

        printf("%d ", data);
    }

    printf("\n\n");

    return 0;
}
