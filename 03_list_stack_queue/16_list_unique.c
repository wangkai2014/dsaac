/* This program delete all duplicates in the list */
#include "utils.h"
#include "list.h"

int create_array(int **in_arr, int *in_size);
int list_unique(struct list *head);

int main()
{
    int result = SUCCESS;
    int size = 0;
    int *arr = NULL;
    struct list *head = NULL;

    /* genrate datas for array */
    result = create_array(&arr, &size);
    if (SUCCESS != result)
    {
        printf("failed to create array!\n");
        return 0;
    }

    /* create a list */
    result = list_create_from_int_arr(&head, arr, size);
    if (SUCCESS != result)
    {
        printf("failed to create list from integer array!\n");
        return 0;
    }

    printf("\nAt the beginning, the list is:\n");
    list_print_int(head);

    /* delete duplicates */
    result = list_unique(head);
    if (SUCCESS != result)
    {
        printf("failed to delete all duplicates in the list!\n");
        return 0;
    }

    printf("\nAfter deleting all duplicates, the list is\n");
    list_print_int(head);

    return 0;
}

int create_array(int **in_arr, int *in_size)
{
    int *arr = NULL;
    int size = 0;
    int pos = 0;

    if ((NULL == in_arr) || (NULL == in_size))
    {
        printf("null pointer!\n");
        return NUL_PTR;
    }

    printf("Enter array's size: ");
    scanf("%d", &size);

    arr = (int *)malloc(sizeof(int) * size);
    if (NULL == arr)
    {
        printf("failed to malloc memory for arr!\n");
        return MALLOC_FAIL;
    }

    srand(time(NULL));
    
    for (pos = 0; pos < size; pos++)
    {
        arr[pos] = rand() % size;
    }

    *in_arr = arr;
    *in_size = size;

    return SUCCESS;
}

int list_unique(struct list *head)
{
    struct list *cur = head->next;
    struct list *other = NULL;
    struct list *dupli = NULL;

    while (NULL != cur)
    {
        other = cur;

        while (NULL != other->next)
        {
            if (data_is_equal(cur->data, other->next->data))
            {
                dupli = other->next;
                other->next = dupli->next;

                free(dupli->data);
                free(dupli);
                dupli = NULL;
            }
            else
            {
                other = other->next;
            }
        }

        cur = cur->next;
    }

    return SUCCESS;
}
