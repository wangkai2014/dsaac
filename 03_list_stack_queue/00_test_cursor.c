#include "utils.h"
#include "cursor.h"

int main()
{
    int result;
    int pos;
    int data = 0;
    int arr[10];
    int head = 0;

    // test list_init
    cursor_init();

    head = list_init();
    if (0 == head)
    {
        printf("failed to init list!\n");
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
        arr[pos] = (pos + 1) * (pos + 2);
    }

    // test push_back
    for (pos = 0; pos < 10; pos++)
    {
        result = list_push_back(head, arr[pos]);
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
        data = list_pop_back(head);
        if (0 == data)
        {
            printf("failed to pop back the list.[%d]\n", pos);
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
        result = list_push_front(head, arr[pos]);
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
        data = list_pop_front(head);
        if (0 == data)
        {
            printf("failed to pop front the list.[%d]\n", pos);
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
