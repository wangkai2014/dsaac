/* This program delete all duplicates in the list */
#include "utils.h"
#include "list.h"

int create_array(int **in_arr, int *in_size);
void sort_array(int *arr, int num);
void qsort_array(int *arr, int left, int right);
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

    sort_array(arr, size);

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

void qsort_array(int *arr, int left, int right)
{
    int cur_left = left + 1;
    int cur_right = right;
    int tmp = 0;

    if (left >= right)
    {
        return;
    }

    while (cur_left <= cur_right)
    {
        if (arr[cur_left] > arr[left])
        {
            tmp = arr[cur_left];
            arr[cur_left] = arr[cur_right];
            arr[cur_right] = tmp;
            cur_right--;
        }
        else
        {
            cur_left++;
        }
    }

    tmp = arr[left];
    arr[left] = arr[cur_right];
    arr[cur_right] = tmp;

    qsort_array(arr, left, cur_right-1);
    qsort_array(arr, cur_left, right);
}

void sort_array(int *arr, int size)
{
    qsort_array(arr, 0, size - 1);
}

int list_unique(struct list *head)
{
    struct list *cur = head->next;
    struct list *next = cur->next;

    while ((NULL != cur) && (NULL != cur->next))
    {
        if (data_is_equal(cur->data, next->data))
        {
            cur->next = next->next;
            free(next->data);
            free(next);
        }
        else
        {
            cur = cur->next;
        }

        next = cur->next;
    }

    return SUCCESS;
}
