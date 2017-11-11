#include "utils.h"
#include "aqueue.h"

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

void operate_queue(queue *que, int operation);
void test_queue_init(queue *que);
void test_queue_enqueue(queue que);
void test_queue_dequeue(queue que);
void test_queue_front(queue que);

int main()
{
    int operation = 0;
    queue que = NULL;

    while (operation < OPER_QUIT)
    {
        printf("1.init 2.clear 3.enqueue 4.dequeue 5.front 6.print 7.quit\n");
        printf("Enter operation: ");
        scanf("%d", &operation);

        operate_queue(&que, operation);
    }

    return 0;
}

void operate_queue(queue *que, int operation)
{
    switch (operation)
    {
        case OPER_INIT:
        {
            test_queue_init(que);
            break;
        }

        case OPER_CLEAR:
        {
            queue_clear(que);
            break;
        }

        case OPER_ENQUE:
        {
            test_queue_enqueue(*que);
            break;
        }

        case OPER_DEQUE:
        {
            test_queue_dequeue(*que);
            break;
        }
    
        case OPER_FRONT:
        {
            test_queue_front(*que);
            break;
        }

        case OPER_PRINT:
        {
            queue_print(*que);
            break;
        }

        default:
            break;
    }
}

void test_queue_init(queue *que)
{
    int result = SUCCESS;
    int size = 0;

    printf("Enter queue's size: ");
    scanf("%d", &size);

    result = queue_init(que, size);
    if (SUCCESS != result)
    {
        printf("failed to init queue! size = %d.\n", size);
    }
    else
    {
        printf("init queue successfully.\n");
    }
}

void test_queue_enqueue(queue que)
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

    for (pos = 0; pos < num; pos++)
    {
        scanf("%d", arr + pos);
    }

    for (pos = 0; pos < num; pos++)
    {
        result = queue_enqueue(que, arr[pos]);
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

void test_queue_dequeue(queue que)
{
    int result = SUCCESS;
    int pos = 0;
    int num = 0;
    int elem = 0;

    printf("Enter elements' num: ");
    scanf("%d", &num);

    for (pos = 0; pos < num; pos++)
    {
        result = queue_dequeue(que, &elem);
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

void test_queue_front(queue que)
{
    int result = SUCCESS;
    int front = 0;

    result = queue_front(que, &front);
    if (SUCCESS != result)
    {
        printf("failed to get the front of the queue!\n");
    }
    else
    {
        printf("queue's front is: %d.\n", front);
    }
}
