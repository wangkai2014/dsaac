#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "list.h"

int main()
{
    int arr[10] = {1,1};
    int result;
    int pos;
    struct list *head = NULL;

    for (pos = 0; pos < 8; pos++)
    {
        arr[pos + 2] = arr[pos + 1] + arr[pos];
    }

    result = list_create_from_int_arr(&head, arr, 10);
    if (SUCCESS != result)
    {
        error("failed to create list!");
    }
    else
    {
        list_print_int(head);
        list_clear(head);
    }

    return 0;
}

