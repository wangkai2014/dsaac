#include "utils.h"
#include "list.h"

int main()
{
    int result;
    int pos;
    int data = 0;
    int arr[10];
    List *head = NULL;

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
        result = list_push_back(head, arr + pos, sizeof(int));
        if (SUCCESS != result)
        {
            printf("err %d: failed to push back the list.\n", result);
            return 0;
        }
    }

    printf("After push back, the list is: \n");
    list_print_int(head);

    // test pop_back
    printf("Now we pop back the list: \n");
    for (pos = 0; pos < 10; pos++)
    {
        result = list_pop_back(head, &data, sizeof(int));
        if (SUCCESS != result)
        {
            printf("err %d: failed to pop back the list.\n", result);
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
        result = list_push_front(head, arr + pos, sizeof(int));
        if (SUCCESS != result)
        {
            printf("err %d: failed to push front the list.\n", result);
            return 0;
        }
    }

    printf("After push front, the list is: \n");
    list_print_int(head);

    // test pop_front
    printf("Now we pop front the list: \n");
    for (pos = 0; pos < 10; pos++)
    {
        result = list_pop_front(head, &data, sizeof(int));
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
