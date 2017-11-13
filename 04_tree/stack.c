#include "utils.h"
#include "stack.h"

static int stack_create(Stack **in_stck, void *data, int data_size)
{
    int result = 0;
    Stack *stck = NULL;

    stck = (Stack *)malloc(sizeof(Stack));
    if (NULL == stck)
    {
        printf("failed to malloc memory for Stack!\n");
        return MALLOC_FAIL;
    }

    stck->data = malloc(data_size);
    if (NULL == stck->data)
    {
        printf("failed to malloc memory for Stack's data!\n");
        return MALLOC_FAIL;
    }

    memcpy(stck->data, data, data_size);
    stck->next = NULL;

    *in_stck = stck;

    return SUCCESS;
}

int stack_init(Stack **in_stck, int data_size)
{
    int result = SUCCESS;
    void *data = NULL;

    data = malloc(data_size);
    if (NULL == data)
    {
        printf("failed to malloc memory for data!\n");
        return 0;
    }

    memset(data, 0, data_size);

    result = stack_create(in_stck, data, data_size);
    if (SUCCESS != result)
    {
        printf("failed to create Stack!\n");
    }

    return result;
}

inline int stack_is_empty(Stack *stck)
{
    return ((stck->next == NULL)? TRUE : FALSE);
}

int stack_push(Stack *in_stck, void *data, int data_size)
{
    int result = SUCCESS;
    Stack *stck = NULL;

    result = stack_create(&stck, data, data_size);
    if (SUCCESS != result)
    {
        printf("failed to create Stack!\n");
        return result;
    }

    stck->next = in_stck->next;
    in_stck->next = stck;

    return SUCCESS;
}

int stack_pop(Stack *in_stck, void *data, int data_size)
{
    int result = SUCCESS;
    Stack *stck = in_stck->next;

    if (stack_is_empty(in_stck))
    {
        printf("cannot pop empty Stack!\n");
        return UNDERFLOW;
    }

    in_stck->next = stck->next;
    memcpy(data, stck->data, data_size);

    free(stck->data);
    free(stck);
    stck = NULL;

    return SUCCESS;
}

int stack_top(Stack *stck, void *data, int data_size)
{
    if (stack_is_empty(stck))
    {
        printf("cannot get the top of an empty Stack!\n");
        return UNDERFLOW;
    }

    memcpy(data, stck->next->data, data_size);

    return SUCCESS;
}

void stack_clear(Stack **in_stck)
{
    Stack *stck = NULL;
    
    while (NULL != *in_stck)
    {
        stck = *in_stck;
        *in_stck = stck->next;
        free(stck->data);
        free(stck);
    }
}
