#include "utils.h"
#include "list.h"

static void print_list(struct list *head);

int main()
{
    int result;
    int pos;
    int data = 0;
    int arr[10];
    struct list *head = NULL;

    // test list_init
    result = list_init(&head, sizeof(int));
    if (SUCCESS != result)
    {
        print_error("failed to initialize list!");
        return 0;
    }

    // test list_is_empty
    if (list_is_empty(head))
    {
        printf("OK. The list should be empty after init.\n");
    }
    else
    {
        printf("ERROR. The list is not empty after init.\n");
    }

    for (pos = 0; pos < 10; pos++)
    {
        arr[pos] = pos * (pos + 1);
    }

    // test push_back
    for (pos = 0; pos < 10; pos++)
    {
        result = list_push_back(head, arr + pos);
        if (SUCCESS != result)
        {
            printf("err %d: failed to push back the list.\n", result);
            return 0;
        }
    }

    printf("After push back, the list is: \n");
    print_list(head);

    // test pop_back
    printf("Now we pop back the list: \n");
    for (pos = 0; pos < 10; pos++)
    {
        result = list_pop_back(head, &data);
        if (SUCCESS != result)
        {
            printf("err %d: failed to pop back the lsit.\n", result);
            return 0;
        }
        else
        {
            printf("%d ", data);
        }
    }

    printf("\n");

    // test push_front
    for (pos = 0; pos < 10; pos++)
    {
        result = list_push_front(head, arr + pos);
        if (SUCCESS != result)
        {
            printf("err %d: failed to push front the list.\n", result);
            return 0;
        }
    }

    printf("After push front, the list is: \n");
    print_list(head);

    // test pop_front
    printf("Now we pop front the list: \n");
    for (pos = 0; pos < 10; pos++)
    {
        result = list_pop_front(head, &data);
        if (SUCCESS != result)
        {
            printf("err %d: failed to pop front the lsit.\n", result);
            return 0;
        }
        else
        {
            printf("%d ", data);
        }
    }

    printf("\n");

    return 0;
}

static void print_list(struct list *head)
{
    struct list *cur = head->next;

    while (NULL != cur)
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }
    printf("\n");
}
