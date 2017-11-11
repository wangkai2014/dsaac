#include "utils.h"
#include "lqueue.h"

int queue_init(queue *in_que)
{
    int result = SUCCESS;
    queue que;

    que = (queue)malloc(sizeof(*que));
    if (NULL == que)
    {
        printf("failed to malloc memory for que when init!\n");
        return MALLOC_FAIL;
    }

    result = list_init(&que->head, sizeof(int));
    if (SUCCESS != result)
    {
        printf("failed to init list of queue when init!\n");
        return result;
    }

    que->size = 0;
    *in_que = que;

    return SUCCESS;
}

void queue_clear(queue *que)
{
    if ((NULL == que) || (NULL == *que))
    {
        printf("failed to clear queue because it's null!\n");
        return;
    }

    list_clear((*que)->head);

    free(*que);
    *que = NULL;
}

int queue_is_empty(queue que)
{
    return ((que->size == 0)? TRUE : FALSE);
}

int queue_enqueue(queue que, int elem)
{
    int result = SUCCESS;
    struct node *new_node = NULL;

    if (NULL == que)
    {
        printf("failed to enqueue element because the queue is null!\n");
        return NUL_PTR;
    }

    result = list_push_front(que->head, &elem);
    if (SUCCESS != result)
    {
        printf("failed to push front element %d to queue!\n", elem);
        return result;
    }

    que->size++;

    return SUCCESS;
}

int queue_dequeue(queue que, int *elem)
{
    int result = SUCCESS;

    if ((NULL == que) || (NULL == elem))
    {
        printf("failed to dequeue element because of null pointer!\n");
        return NUL_PTR;
    }

    if (queue_is_empty(que))
    {
        printf("failed to dequeue element because the queue is empty!\n");
        return UNDERFLOW;
    }

    result = list_pop_back(que->head, elem);
    if (SUCCESS != result)
    {
        printf("failed to pop back element from queue!\n");
        return result;
    }

    que->size--;

    return SUCCESS;
}

int queue_front(queue que, int *front)
{
    struct list *last = NULL;

    if ((NULL == que) || (NULL == front))
    {
        printf("failed to get front of the queue because of null pointer!\n");
        return NUL_PTR;
    }

    if (queue_is_empty(que))
    {
        printf("failed to get front of the queue because it's empty!\n");
        return UNDERFLOW;
    }

    last = list_last(que->head);
    *front = *(int *)last->data;

    return SUCCESS;
}

void queue_print(queue que)
{
    int pos;

    if (NULL == que)
    {
        printf("failed to print queue because it's null!\n");
        return;
    }

    printf("\nsize: %d", que->size);
    printf("\nelements: ");

    list_print_int(que->head);
}
