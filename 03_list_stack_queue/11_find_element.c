#include "utils.h"
#include "list.h"

int main()
{
    char go_on = 'y';
    int *arr = NULL;
    int size = 0;
    int pos = 0;
    int data = 0;
    int algorithm_id = 0;
    int result = SUCCESS;
    struct list *head = NULL;
    struct list *target = NULL;

    while (go_on = 'y')
    {
        printf("Enter list's size: ");
        scanf("%d", &size);

        printf("Enter target data: ");
        scanf("%d", &data);

        printf("Enter the algorithem id(0. recursive, 1. nonrecursive): ");
        scanf("%d", &algorithm_id);

        arr = (int *)malloc(sizeof(int) * size);
        if (NULL == arr)
        {
            print_error("failed to malloc memory for arr!");
            return 0;
        }

        for (pos = 0; pos < size; pos++) 
        {
            arr[pos] = (pos+1) * (pos + 2);
        }

        result = list_create_from_int_arr(&head, arr, size);
        if (SUCCESS != result)
        {
            print_error("failed to create list from int array!");
            free(arr);
            return 0;
        }

        if (0 == algorithm_id)
        {
            target = list_find_recursively(head, &data);
        }
        else
        {
            target = list_find(head, &data);
        }

        if (NULL == target)
        {
            printf("not found.\n");
        }
        else
        {
            printf("found.\n");
        }

        free(arr);
        list_clear(head);

        arr = NULL;
        head = NULL;
        target = NULL;

        printf("Continue? ('y' or 'n'): ");
        scanf(" %c", &go_on);
    }

    return 0;
}
