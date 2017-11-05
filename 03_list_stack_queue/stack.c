#include "utils.h"
#include "stack.h"

int stack_data_size = 0;

static int stack_create(stack *in_stck, void *data)
{
    int result = 0;
    stack stck = NULL;

    stck = (stack)malloc(sizeof(stack));
    if (NULL == stck)
    {
        printf("failed to malloc memory for stack!\n");
        return MALLOC_FAIL;
    }

    stck->data = malloc(stack_data_size);
    if (NULL == stck->data)
    {
        printf("failed to malloc memory for stack's data!\n");
        return MALLOC_FAIL;
    }

    memcpy(stck->data, data, stack_data_size);
    stck->next = NULL;

    *in_stck = stck;

    return SUCCESS;
}

int stack_init(stack *in_stck, int elem_size)
{
    int result = SUCCESS;
    void *data = NULL;

    stack_data_size = elem_size;

    data = malloc(elem_size);
    if (NULL == data)
    {
        printf("failed to malloc memory for data!\n");
        return 0;
    }

    memset(data, 0, elem_size);

    result = stack_create(in_stck, data);
    if (SUCCESS != result)
    {
        printf("failed to create stack!\n");
    }

    return result;
}

inline int stack_is_empty(stack stck)
{
    return ((stck->next == NULL)? TRUE : FALSE);
}

int stack_push(stack stck, void *data)
{
    int result = SUCCESS;
    stack cur = NULL;

    result = stack_create(&cur, data);
    if (SUCCESS != result)
    {
        printf("failed to create stack!\n");
        return result;
    }

    cur->next = stck->next;
    stck->next = cur;

    return SUCCESS;
}

int stack_pop(stack stck, void *data)
{
    int result = SUCCESS;
    stack first = stck->next;

    if (stack_is_empty(stck))
    {
        printf("cannot pop empty stack!\n");
        return UNDERFLOW;
    }

    stck->next = first->next;
    memcpy(data, first->data, stack_data_size);

    free(first->data);
    free(first);
    first = NULL;

    return SUCCESS;
}

int stack_top(stack stck, void *data)
{
    if (stack_is_empty(stck))
    {
        printf("cannot get the top of an empty stack!\n");
        return UNDERFLOW;
    }

    memcpy(data, stck->next->data, stack_data_size);

    return SUCCESS;
}

void stack_clear(stack stck)
{
    stack cur = stck->next;
    
    while (NULL != cur)
    {
        stck->next = cur->next;
        free(cur->data);
        free(cur);

        cur = stck->next;
    }

    free(stck->data);
    free(stck);
    stack_data_size = 0;
}
