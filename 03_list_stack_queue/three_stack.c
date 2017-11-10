#include "utils.h"
#include "three_stack.h"

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
    stck->third_num = 0;
    stck->third_start = size / 2;

    *in_stck = stck;
    stck = NULL;

    return SUCCESS;
}

int stack_is_empty(stack stck, int stck_id)
{
    switch (stck_id)
    {
        case 0:
        {
            return ((stck->first_num == 0) ? TRUE : FALSE);
        }

        case 1:
        {
            return ((stck->second_num == 0) ? TRUE : FALSE);
        }

        case 2:
        {
            return ((stck->third_num == 0) ? TRUE : FALSE);
        }

        default:
        {
            return TRUE;
        }
    }
}

int stack_is_full(stack stck, int stck_id)
{
    return ((stck->first_num + stck->second_num + stck->third_num < stck->size) ? FALSE : TRUE);
}

void stack_adjust(stack stck, int stck_id)
{
    int left = stck->size - stck->first_num - stck->second_num - stck->third_num;
    int shift = (left + 1) / 2;
    int pos;

    if ((stck_id == 0) && (stck->first_num == stck->third_start))
    {
        for (pos = stck->third_start + stck->third_num - 1; pos >= stck->third_start; pos--)
        {
            stck->arr[pos + shift] = stck->arr[pos];
        }

        stck->third_start += shift;
    }
    else if ((stck_id > 0) && (stck->third_start + stck->third_num + stck->second_num == stck->size))
    {
        for (pos = stck->third_start; pos < stck->third_start + stck->third_num; pos++)
        {
            stck->arr[pos - shift] = stck->arr[pos];
        }

        stck->third_start -= shift;
    }
}

int stack_push(stack stck, int stck_id, int elem)
{
    if ((NULL == stck) || (stck_id >= STACK_NUM))
    {
        printf("Invalid input! stck_id=%d, elem=%d.\n", stck_id, elem);
        return INVALID_INPUT;
    }

    if (stack_is_full(stck, stck_id))
    {
        printf("failed to push stack %d since it's full!\n", stck_id);
        return OVERFLOW;
    }

    stack_adjust(stck, stck_id);

    switch (stck_id)
    {
        case 0 :
        {
            stck->arr[stck->first_num++] = elem;
            break;
        }

        case 1 :
        {
            stck->arr[stck->size - 1 - stck->second_num] = elem;
            stck->second_num++;
            break;
        }

        case 2 :
        {
            stck->arr[stck->third_start + stck->third_num] = elem;
            stck->third_num++;
            break;
        }

        default:
            break;
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

    if (stack_is_empty(stck, stck_id))
    {
        printf("failed to pop element from stack %d since it's empty!\n", stck_id);
        return UNDERFLOW;
    }

    switch (stck_id)
    {
        case 0:
        {
            *elem = stck->arr[stck->first_num - 1];
            stck->first_num--;
            break;
        }

        case 1:
        {
            *elem = stck->arr[stck->size - stck->second_num - 1];
            stck->second_num--;
            break;
        }

        case 2:
        {
            *elem = stck->arr[stck->third_start + stck->third_num - 1];
            stck->third_num--;
            break;
        }

        default:
        {
            break;
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

    if (stack_is_empty(stck, stck_id))
    {
        printf("failed to get the top of stack %d since it's empty!\n", stck_id);
        return UNDERFLOW;
    }

    switch (stck_id)
    {
        case 0:
        {
            *elem = stck->arr[stck->first_num - 1];
            break;
        }

        case 1:
        {
            *elem = stck->arr[stck->size - stck->second_num - 1];
            break;
        }

        case 2:
        {
            *elem = stck->arr[stck->third_start + stck->third_num - 1];
            break;
        }

        default:
        {
            break;
        }
    }

    return SUCCESS;
}

int stack_print(stack stck)
{
    int pos;

    if (NULL == stck)
    {
        printf("null pointer!\n");
        return NUL_PTR;
    }

    printf("\nS0: ");
    for (pos = 0; pos < stck->first_num; pos++)
    {
        printf("%d ", stck->arr[pos]);
    }

    printf("\n");
    for (pos = stck->first_num; pos < stck->third_start; pos++)
    {
        printf(" *");
    }

    printf("\nS2: ");
    for (pos = stck->third_start; pos < stck->third_start + stck->third_num; pos++)
    {
        printf("%d ", stck->arr[pos]);
    }

    printf("\n");
    for (pos = stck->third_start + stck->third_num; pos < stck->size - stck->second_num; pos++)
    {
        printf(" *");
    }

    printf("\nS1: ");
    for (pos = stck->size - 1; pos >= stck->size - stck->second_num; pos--)
    {
        printf("%d ", stck->arr[pos]);
    }

    printf("\n");

    return SUCCESS;
}

int stack_clear(stack *in_stck)
{
    stack stck = NULL;

    if (NULL == in_stck)
    {
        printf("null pointer!\n");
        return NUL_PTR;
    }

    stck = *in_stck;

    if (NULL != stck)
    {
        if (NULL != stck->arr)
        {
            free(stck->arr);
            stck->arr = NULL;
        }

        free(stck);
        stck = NULL;
        *in_stck = NULL;
    }

    return SUCCESS;
}
