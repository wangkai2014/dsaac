#include "utils.h"
#include "dlist.h"

void list_swap_elements(struct list *head, struct list *prev);

int main()
{
    int arr[10];
    int pos = 0;
    int result = 0;
    struct list *head = NULL;

    for (pos = 0; pos < 10; pos++)
    {
        arr[pos] = pos * pos * pos * pos;
    }

    result = list_create_from_int_arr(&head, arr, 10);
    if (SUCCESS != result)
    {
        error("failed to create list!");
        return 0;
    }

    printf("before swaping, the doubly linked list is: ");
    list_print_int(head);

    list_swap_elements(head, head->next);

    printf("after swaping, the doubly linked list is: ");
    list_print_int(head);

    return 0;
}

void list_swap_elements(struct list *head, struct list *prev)
{
    struct list *cur = NULL;
    struct list *next = NULL;

    if ((NULL == head) || (NULL == prev))
    {
        error("null pointer!");
        return;
    }

    cur = prev->next;
    next = cur->next;

    prev->next = next;
    cur->next = next->next;
    next->next = cur;

    cur->prev = next;
    next->prev = prev;
    if (NULL != cur->next)
    {
        cur->next->prev = cur;
    }
}
