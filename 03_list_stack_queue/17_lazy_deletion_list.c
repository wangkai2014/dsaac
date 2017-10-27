#include "utils.h"
#include "lazy_list.h"

int main()
{
    int result;
    int pos;
    int data = 0;
    int arr[10];
    struct list *head = NULL;
    struct list *prev = NULL;

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
        printf("\nOK. The list should be empty after init.\n");
    }
    else
    {
        printf("\nERROR. The list is not empty after init.\n");
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
            printf("\nerr %d: failed to push back the list.\n", result);
            return 0;
        }
    }

    printf("\nAfter push back, the list is: \n");
    list_print_int(head);

    // test delete
    printf("\nNow we delete the list: \n");
    for (pos = 0; pos < 10; pos++)
    {
        list_del(head, arr + pos);
        list_print_int(head);
    }

    printf("\n\n");

    // test push_back
    for (pos = 0; pos < 10; pos++)
    {
        result = list_push_back(head, arr + pos);
        if (SUCCESS != result)
        {
            printf("\nerr %d: failed to push front the list.\n", result);
            return 0;
        }
    }

    printf("\nAfter push back, the list is: \n");
    list_print_int(head);

    // test delete
    printf("\nNow we delete the list: \n");
    for (pos = 0; pos < 4; pos++)
    {
        list_del(head, arr + pos);
        list_print_int(head);
    }

    printf("\n\n");

    // test insert
    prev = head;
    printf("\nNow we insert the list: \n");
    for (pos = 0; pos < 4; pos++)
    {
        result = list_insert(head, prev, arr + pos);
        if (SUCCESS != result)
        {
            printf("\nerr %d: failed to insert the lsit.\n", result);
            return 0;
        }
        else
        {
            list_print_int(head);
        }

        prev = prev->next;
    }

    printf("\n\n");

    return 0;
}
