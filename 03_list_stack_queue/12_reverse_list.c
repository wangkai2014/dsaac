#include "utils.h"
#include "list.h"

int main()
{
    int *arr = NULL;
    int size = 0;
    int pos = 0;
    int result = SUCCESS;
    struct list *head = NULL;

    printf("Enter list's size: ");
    scanf("%d", &size);

    arr = (int *)malloc(sizeof(int) * size);
    if (NULL == arr)
    {
        print_error("failed to malloc memory for arr!");
        return 0;
    }

    for (pos = 0; pos < size; pos++)
    {
        arr[pos] = (pos + 1) * (pos + 2);
    }

    result = list_create_from_int_arr(&head, arr, size);
    if (SUCCESS != result)
    {
        print_error("failed to create list from int array!");
        free(arr);
        return 0;
    }

    printf("before reversing, the list is:\n");
    list_print_int(head);

    result = list_reverse(head);
    if (SUCCESS != result)
    {
        print_error("failed to reverse list!");
        free(arr);
        list_clear(head);
        return 0;
    }

    printf("after reversing, the list is:\n");
    list_print_int(head);

    free(arr);
    list_clear(head);

    return 0;
}
