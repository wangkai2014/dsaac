#include "utils.h"
#include "queue.h"

int queue_init(Queue **in_queue)
{
    int result = SUCCESS;
    Queue *queue;

    queue = (Queue *)malloc(sizeof(Queue));
    if (NULL == queue)
    {
        printf("failed to malloc memory for que when init!\n");
        return MALLOC_FAIL;
    }

    result = list_init(&queue->head, sizeof(int));
    if (SUCCESS != result)
    {
        printf("failed to init list of queue when init!\n");
        return result;
    }

    queue->size = 0;
    *in_queue = queue;

    return SUCCESS;
}

void queue_clear(Queue **queue)
{
    if ((NULL == queue) || (NULL == *queue))
    {
        printf("failed to clear queue because it's null!\n");
        return;
    }

    list_clear(&(*queue)->head);

    free(*queue);
    *queue = NULL;
}

int queue_is_empty(Queue *queue)
{
    return ((queue->size == 0)? TRUE : FALSE);
}

int queue_enqueue(Queue *queue, void *data, int data_size)
{
    int result = SUCCESS;

    if ((NULL == queue) || (NULL == data))
    {
        printf("failed to enqueue data because of null pointer!\n");
        return NUL_PTR;
    }

    result = list_push_front(queue->head, data, data_size);
    if (SUCCESS != result)
    {
        printf("failed to push front data to queue!\n");
        return result;
    }

    queue->size++;

    return SUCCESS;
}

int queue_dequeue(Queue *queue, void *data, int data_size)
{
    int result = SUCCESS;

    if ((NULL == queue) || (NULL == data))
    {
        printf("failed to dequeue element because of null pointer!\n");
        return NUL_PTR;
    }

    if (queue_is_empty(queue))
    {
        printf("failed to dequeue element because the queue is empty!\n");
        return UNDERFLOW;
    }

    result = list_pop_back(queue->head, data, data_size);
    if (SUCCESS != result)
    {
        printf("failed to pop back element from queue!\n");
        return result;
    }

    queue->size--;

    return SUCCESS;
}

int queue_front(Queue *queue, void *front, int data_size)
{
    List *last = NULL;

    if ((NULL == queue) || (NULL == front))
    {
        printf("failed to get front of the queue because of null pointer!\n");
        return NUL_PTR;
    }

    if (queue_is_empty(queue))
    {
        printf("failed to get front of the queue because it's empty!\n");
        return UNDERFLOW;
    }

    last = list_last(queue->head);

    memcpy(front, last->data, data_size);

    return SUCCESS;
}

void queue_print(Queue *queue)
{
    int pos;

    if (NULL == queue)
    {
        printf("failed to print queue because it's null!\n");
        return;
    }

    printf("\nsize: %d", queue->size);
    printf("\nelements: ");

    list_print_int(queue->head);
}
