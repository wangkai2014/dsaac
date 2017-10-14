#include "utils.h"
#include "list.h"

struct list *list_union(struct list *head_a, struct list *head_b);

int main()
{
    struct list *head_a = NULL;
    struct list *head_b = NULL;
    struct list *head_union = NULL;
    int arr_a[10];
    int arr_b[8];
    int result = 0;
    int pos;

    for (pos = 0; pos < 10; pos++)
    {
        arr_a[pos] = pos;
    }

    for (pos = 0; pos < 8; pos++)
    {
        arr_b[pos] = 2 * pos;
    }

    result = list_create_from_int_arr(&head_a, arr_a, 10);
    if (SUCCESS != result)
    {
        error("failed to create list a!");
        return 0;
    } 
    
    result = list_create_from_int_arr(&head_b, arr_b, 8); 
    if (SUCCESS != result)
    {
        error("failed to create list b!");
        return 0;
    }

    head_union = list_union(head_a, head_b);
    if (NULL == head_union)
    {
        error("failed to union list a and list b!");
        return 0;
    }

    printf("The union of list a and list b is :\n");
    list_print_int(head_union);

    return 0;
}

struct list *list_union(struct list *head_a, struct list *head_b)
{
    struct list *head_union = NULL;
    struct list *cur_a = NULL;
    struct list *cur_b = NULL;
    struct list *cur_union = NULL;
    void *data = NULL;
    int result = 0;

    if ((NULL == head_a) || (NULL == head_b))
    {
        error("null pointer!");
        return NULL;
    }

    result = list_init(&head_union, sizeof(int));
    if (SUCCESS != result)
    {
        error("failed to init list!");
        return NULL;
    }

    cur_a = head_a->next;
    cur_b = head_b->next;
    cur_union = head_union;

    while ((NULL != cur_a) && (NULL != cur_b))
    {
        if ((*(int *)cur_a->data) < (*(int *)cur_b->data))
        {
            data = cur_a->data;
            cur_a = cur_a->next;
        }
        else if ((*(int *)cur_a->data) > (*(int *)cur_b->data))
        {
            data = cur_b->data;
            cur_b = cur_b->next;
        }
        else
        {
            data = cur_a->data;
            cur_a = cur_a->next;
            cur_b = cur_b->next;
        }

        result = list_insert(head_union, cur_union, data);
        if (SUCCESS != result)
        {
            error("failed to insert list!");
            return NULL;
        }

        cur_union = cur_union->next;
    }

    if (NULL == cur_a)
    {
        cur_a = cur_b;
    }

    while (NULL != cur_a)
    {
        result = list_insert(head_union, cur_union, cur_a->data);
        if (SUCCESS != result)
        {
            error("failed to insert list!");
            return NULL;
        }

        cur_a = cur_a->next;
        cur_union = cur_union->next;
    }

    return head_union;
}
