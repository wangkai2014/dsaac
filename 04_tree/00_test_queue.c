#include "utils.h"
#include "queue.h"

enum OPER_CODE
{
    OPER_INIT   = 1,
    OPER_CLEAR  = 2,
    OPER_ENQUE  = 3,
    OPER_DEQUE  = 4,
    OPER_FRONT  = 5,
    OPER_PRINT  = 6,
    OPER_QUIT   = 7,
    OPER_INVALID
};

void operate_queue(Queue **queue, int operation);
void test_queue_init(Queue **queue);
void test_queue_enqueue(Queue *queue);
void test_queue_dequeue(Queue *queue);
void test_queue_front(Queue *queue);

int main()
{
    int operation = 0;
    Queue *queue = NULL;

    while (operation < OPER_QUIT)
    {
        printf("\n1.init 2.clear 3.enqueue 4.dequeue 5.front 6.print 7.quit");
        printf("\nEnter operation: ");
        scanf("%d", &operation);

        operate_queue(&queue, operation);
    }

    if (NULL != queue)
    {
        queue_clear(&queue);
    }

    return 0;
}

void operate_queue(Queue **queue, int operation)
{
    switch (operation)
    {
        case OPER_INIT:
        {
            test_queue_init(queue);
            break;
        }

        case OPER_CLEAR:
        {
            queue_clear(queue);
            break;
        }

        case OPER_ENQUE:
        {
            test_queue_enqueue(*queue);
            break;
        }

        case OPER_DEQUE:
        {
            test_queue_dequeue(*queue);
            break;
        }
    
        case OPER_FRONT:
        {
            test_queue_front(*queue);
            break;
        }

        case OPER_PRINT:
        {
            queue_print(*queue);
            break;
        }

        default:
            break;
    }
}

void test_queue_init(Queue **queue)
{
    int result = SUCCESS;
    int size = 0;

    result = queue_init(queue, sizeof(int));
    if (SUCCESS != result)
    {
        printf("failed to init queue!\n");
    }
    else
    {
        printf("init queue successfully.\n");
    }
}

void test_queue_enqueue(Queue *queue)
{
    int result = SUCCESS;
    int num = 0;
    int pos = 0;
    int *arr = NULL;

    printf("Enter elements' num: ");
    scanf("%d", &num);

    arr = (int *)malloc(sizeof(int) * num);
    if (NULL == arr)
    {
        printf("failed to malloc memory for arr when enqueue!\n");
        return;
    }

    printf("Enter elements' value: ");
    for (pos = 0; pos < num; pos++)
    {
        scanf("%d", arr + pos);
    }

    for (pos = 0; pos < num; pos++)
    {
        result = queue_enqueue(queue, arr + pos, sizeof(int));
        if (SUCCESS != result)
        {
            printf("failed to enqueue element %d!\n", arr[pos]);
            free(arr);
            return;
        }
    }

    free(arr);

    printf("enqueue successfully.\n");
}

void test_queue_dequeue(Queue *queue)
{
    int result = SUCCESS;
    int pos = 0;
    int num = 0;
    int elem = 0;

    printf("Enter elements' num: ");
    scanf("%d", &num);

    printf("dequeueing...\n");
    for (pos = 0; pos < num; pos++)
    {
        result = queue_dequeue(queue, &elem, sizeof(int));
        if (SUCCESS != result)
        {
            printf("failed to dequeue elment! pos = %d.\n", pos);
        }
        else
        {
            printf("%d ", elem);
        }
    }

    printf("\n");
}

void test_queue_front(Queue *queue)
{
    int result = SUCCESS;
    int front = 0;

    result = queue_front(queue, &front, sizeof(int));
    if (SUCCESS != result)
    {
        printf("failed to get the front of the queue!\n");
    }
    else
    {
        printf("queue's front is: %d.\n", front);
    }
}
