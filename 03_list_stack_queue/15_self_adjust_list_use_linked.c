#include "utils.h"
#include "list.h"

struct list *find(struct list *head, void *data);

int main()
{
    int result = SUCCESS;
    int pos = 0;
    int index = 0;
    int arr[10];
    struct list *head = NULL;
    struct list *cur = NULL;

    result = list_init(&head, sizeof(int));
    if (SUCCESS != result)
    {
        printf("failed to init list!\n");
        return 0;
    }

    for (pos = 0; pos < 10; pos++)
    {
        arr[pos] = pos * (pos + 2);

        result = list_push_front(head, arr + pos);
        if (SUCCESS != result)
        {
            printf("failed to insert list!\n");
            return 0;
        }
    }

    printf("At the beginning, the list is :\n");
    list_print_int(head);

    srand(time(NULL));

    for (pos = 0; pos < 10; pos++)
    {
        index = rand() % 10;

        cur = find(head, arr + index);
        if (NULL == cur)
        {
            printf("failed to find the element %d in the list!\n", arr[index]);
            return 0;
        }

        printf("After finding element %d, the list is:\n", arr[index]);
        list_print_int(head);
    }

    list_clear(head);

    return 0;
}

struct list *find(struct list *head, void *data)
{
    struct list *prev = NULL;
    struct list *cur = NULL;

    if ((NULL == head) || (NULL == data))
    {
        printf("null pointer!\n");
        return NULL;
    }

    prev = list_find_prev(head, data);
    if (NULL == prev)
    {
        printf("not found!\n");
        return NULL;
    }

    cur = prev->next;
    prev->next = cur->next;
    cur->next = head->next;
    head->next = cur;

    return cur;
}
