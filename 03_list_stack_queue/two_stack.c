#include "utils.h"
#include "two_stack.h"

int stack_init(stack *in_stck, int size)
{
    stack stck = NULL;

    if ((NULL == in_stck) || (1 > size))
    {
        printf("Invalid input! size=%d.\n", size);
        return INVALID_INPUT;
    }

    stck = (stack)malloc(sizeof(*stck));
    if (NULL == stck)
    {
        printf("Failed to malloc memory for stack!\n");
        return MALLOC_FAIL;
    }

    stck->arr = (int *)malloc(sizeof(int) * size);
    if (NULL == stck->arr)
    {
        printf("failed to malloc memory for stack's array!\n");
        return MALLOC_FAIL;
    }

    stck->size = size;
    stck->first_num = 0;
    stck->second_num = 0;

    *in_stck = stck;

    return SUCCESS;
}

int stack_push(stack stck, int stck_id, int elem)
{
    if ((NULL == stck) || (stck_id >= STACK_NUM))
    {
        printf("Invalid input! stck_id=%d, elem=%d.\n", stck_id, elem);
        return INVALID_INPUT;
    }

    if (stck->first_num + stck->second_num >= stck->size)
    {
        printf("failed to push stack %d since it's full!\n", stck_id);
        return OVERFLOW;
    }

    if (stck_id == 0)
    {
        stck->arr[stck->first_num++] = elem;
    }
    else
    {
        stck->second_num++;
        stck->arr[stck->size - stck->second_num] = elem;
    }

    return SUCCESS;
}

int stack_pop(stack stck, int stck_id, int *elem)
{
    if ((NULL == stck) || (NULL == elem) || (stck_id >= STACK_NUM))
    {
        printf("Invalid input! stck_id=%d.\n", stck_id);
        return INVALID_INPUT;
    }

    if (stck_id == 0)
    {
        if (stck->first_num <= 0)
        {
            printf("failed to pop element from stack %d since it's empty!\n", stck_id);
            return UNDERFLOW;
        }
        else
        {
            *elem = stck->arr[stck->first_num--];
        }
    }
    else
    {
        if (stck->second_num <= 0)
        {
            printf("failed to pop element from stack %d since it's empty!\n", stck_id);
            return UNDERFLOW;
        }
        else
        {
            *elem = stck->arr[stck->size - stck->second_num];
            stck->second_num--;
        }
    }

    return SUCCESS;
}

int stack_top(stack stck, int stck_id, int *elem)
{
    if ((NULL == stck) || (NULL == elem) || (stck_id >= STACK_NUM))
    {
        printf("Invalid input! stck_id=%d.\n", stck_id);
        return INVALID_INPUT;
    }

    if (stck_id == 0)
    {
        if (stck->first_num <= 0)
        {
            printf("failed to get the top of stack %d since it's empty!\n", stck_id);
            return UNDERFLOW;
        }
        else
        {
            *elem = stck->arr[stck->first_num - 1];
        }
    }
    else
    {
        if (stck->second_num <= 0)
        {
            printf("failed to get the top of  stack %d since it's empty!\n", stck_id);
            return UNDERFLOW;
        }
        else
        {
            *elem = stck->arr[stck->size - stck->second_num];
        }
    }

    return SUCCESS;
}

int stack_print(stack stck, int stck_id)
{
    int pos;

    if ((NULL == stck)  || (stck_id >= STACK_NUM))
    {
        printf("Invalid input! stck_id=%d.\n", stck_id);
        return INVALID_INPUT;
    }

    printf("\nstack %d:\n", stck_id);

    if (stck_id == 0)
    {
        for (pos = 0; pos < stck->first_num; pos++)
        {
            printf("%d ", stck->arr[pos]);
        }

        printf("\n");
    }
    else
    {
        for (pos = stck->size - 1; pos >= (stck->size - stck->second_num); pos--)
        {
            printf("%d ", stck->arr[pos]);
        }
        
        printf("\n");
    }

    return SUCCESS;
}

int stack_clear(stack *stck)
{
    if ((NULL == stck) || (NULL == *stck))
    {
        printf("null pointer!\n");
        return NUL_PTR;
    }

    if (NULL != (*stck)->arr)
    {
        free((*stck)->arr);
    }

    free(*stck);
    *stck = NULL;

    return SUCCESS;
}
