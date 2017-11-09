/* this is the implementation of a special stack, which can find 
 * the smallest element in the stack in O(1) worst case time */
#include "utils.h"
#include "min_stack.h"

static int cmp_data(void *a, void *b)
{
    if (*(int *)a < *(int *)b)
    {
        return -1;
    }
    else if (*(int *)a == *(int *)b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

static int create_node(struct node **in_node, void *data, int size)
{
    int result = 0;
    struct node *new_node = NULL;

    new_node = (struct node *)malloc(sizeof(struct node));
    if (NULL == new_node)
    {
        printf("failed to malloc memory for new node!\n");
        return MALLOC_FAIL;
    }

    new_node->data = malloc(sizeof(char) * size);
    if (NULL == new_node->data)
    {
        printf("failed to malloc memory for stack's data!\n");
        return MALLOC_FAIL;
    }

    memcpy(new_node->data, data, sizeof(char) * size);
    new_node->next = NULL;

    *in_node = new_node;

    return SUCCESS;
}

int stack_init(stack *in_stck, int elem_size)
{
    int result = SUCCESS;
    stack stck = NULL;
    void *data = NULL;

    stck = (stack)malloc(sizeof(struct min_stack));
    if (NULL == stck)
    {
        printf("failed to malloc memory for stck!\n");
        return MALLOC_FAIL;
    }

    stck->data_size = elem_size;

    data = malloc(elem_size);
    if (NULL == data)
    {
        printf("failed to malloc memory for data!\n");
        return 0;
    }

    memset(data, 0, elem_size);

    result = create_node(&(stck->head), data, stck->data_size);
    result != create_node(&(stck->min), data, stck->data_size);
    if (SUCCESS != result)
    {
        printf("failed to create list for stack!\n");
    }

    *in_stck = stck;

    return result;
}

inline int stack_is_empty(stack stck)
{
    return ((stck->head->next == NULL)? TRUE : FALSE);
}

int stack_push(stack stck, void *data)
{
    int result = SUCCESS;
    struct node *new_node = NULL;

    result = create_node(&new_node, data, stck->data_size);
    if (SUCCESS != result)
    {
        printf("failed to create node for head!\n");
        return result;
    }

    new_node->next = stck->head->next;
    stck->head->next = new_node;

    if ((NULL == stck->min->next) || (cmp_data(data, stck->min->next->data) <= 0))
    {
        result = create_node(&new_node, data, stck->data_size);
        if (SUCCESS != result)
        {
            printf("failed to create node for min!\n");
            return result;
        }

        new_node->next = stck->min->next;
        stck->min->next = new_node;
    }

    return SUCCESS;
}

int stack_pop(stack stck, void *data)
{
    int result = SUCCESS;
    struct node *first = stck->head->next;

    if (stack_is_empty(stck))
    {
        printf("cannot pop empty stack!\n");
        return UNDERFLOW;
    }

    stck->head->next = first->next;
    memcpy(data, first->data, stck->data_size);

    free(first->data);
    free(first);

    if (cmp_data(data, stck->min->next->data) == 0)
    {
        first = stck->min->next;
        stck->min->next = first->next;
        free(first->data);
        free(first);
    }

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

    memcpy(data, stck->head->next->data, stck->data_size);

    return SUCCESS;
}

int stack_min(stack stck, void *data)
{
    if (stack_is_empty(stck))
    {
        printf("cannot get the smallest element of an empty stack!\n");
        return UNDERFLOW;
    }

    memcpy(data, stck->min->next->data, stck->data_size);

    return SUCCESS;
}

void stack_print(stack stck)
{
    struct node *cur = stck->head->next;

    if (stack_is_empty(stck))
    {
        printf("empty stack!\n");
        return;
    }

    printf("\nstack: ");
    while (NULL != cur)
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }

    cur = stck->min->next;

    printf("\nmin: ");
    while (NULL != cur)
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }

    printf("\n");
}

void stack_clear(stack *in_stck)
{
    struct node *cur = NULL;
    stack stck = NULL;

    if ((NULL == in_stck) || (NULL == *in_stck))
    {
        return;
    }

    stck = *in_stck;
    
    while (NULL != stck->head->next)
    {
        cur = stck->head->next;
        stck->head->next = cur->next;
        free(cur->data);
        free(cur);
    }

    while (NULL != stck->min->next)
    {
        cur = stck->min->next;
        stck->min->next = cur->next;
        free(cur->data);
        free(cur);
    }

    free(stck->head->data);
    free(stck->min->data);
    free(stck->head);
    free(stck->min);
    free(stck);

    *in_stck = NULL;
}
