#include "utils.h"
#include "aqueue.h"

int queue_init(queue *in_que, int capacity)
{
    int result = SUCCESS;
    queue que;

    que = (queue)malloc(sizeof(*que));
    if (NULL == que)
    {
        printf("failed to malloc memory for que when init!\n");
        return MALLOC_FAIL;
    }

    que->arr = (int *)malloc(sizeof(int) * capacity);
    if (NULL == que->arr)
    {
        printf("failed to malloc memory for que->arr when init!\n");
        return MALLOC_FAIL;
    }

    que->capacity = capacity;
    que->size = 0;
    que->front = 1;
    que->rear = 0;
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

    if (NULL != (*que)->arr)
    {
        free((*que)->arr);
        (*que)->arr = NULL;
    }

    free(*que);
    *que = NULL;
}

int queue_is_empty(queue que)
{
    return ((que->size == 0)? TRUE : FALSE);
}

int queue_is_full(queue que)
{
    return ((que->size == que->capacity)? TRUE : FALSE);
}

int queue_enqueue(queue que, int elem)
{
    if (NULL == que)
    {
        printf("failed to enqueue element because the queue is null!\n");
        return NUL_PTR;
    }

    if (queue_is_full(que))
    {
        printf("failed to enqueue element because the queue is full!\n");
        return OVERFLOW;
    }

    que->rear = ((que->rear == que->capacity - 1)? 0 : que->rear + 1);
    que->arr[que->rear] = elem;
    que->size++;

    return SUCCESS;
}

int queue_dequeue(queue que, int *elem)
{
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

    *elem = que->arr[que->front];
    que->front = ((que->front == que->capacity - 1) ? 0 : que->front + 1);
    que->size--;

    return SUCCESS;
}

int queue_front(queue que, int *front)
{
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

    *front = que->arr[que->front];

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

    printf("\nqueue's info:");
    printf("\ncaparity: %d, size: %d, front: %d, rear: %d.", 
            que->capacity, que->size, que->front, que->rear);

    if (queue_is_empty(que))
    {
        printf("\n");
        return;
    }

    printf("\nelements: ");

    if (que->rear < que->front)
    {
        for (pos = que->front; pos < que->capacity; pos++)
        {
            printf("%d ", que->arr[pos]);
        }

        for (pos = 0; pos <= que->rear; pos++)
        {
            printf("%d ", que->arr[pos]);
        }
    }
    else
    {
        for (pos = que->front; pos <= que->rear; pos++)
        {
            printf("%d ", que->arr[pos]);
        }
    }

    printf("\n");

}
