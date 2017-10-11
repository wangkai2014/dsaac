#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "list.h"

struct list *list_intersect(struct list *first, struct list *second);

int main()
{
    struct list *head_a = NULL;
    struct list *head_b = NULL;
    struct list *head_intersect = NULL;
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

    head_intersect = list_intersect(head_a, head_b);
    if (NULL == head_intersect)
    {
        error("failed to intersect list a and list b!");
        return 0;
    }

    printf("The intersection of list a and list b is :\n");
    list_print_int(head_intersect);

    return 0;
}

struct list *list_intersect(struct list *head_a, struct list *head_b)
{
    struct list *head_intersect = NULL;
    struct list *cur_a = NULL;
    struct list *cur_b = NULL;
    struct list *cur_intersect = NULL;
    int result = 0;

    if ((NULL == head_a) || (NULL == head_b))
    {
        error("null pointer!");
        return NULL;
    }

    result = list_init(&head_intersect, sizeof(int));
    if (SUCCESS != result)
    {
        error("failed to init list intersect!");
        return NULL;
    }

    cur_a = head_a->next;
    cur_b = head_b->next;
    cur_intersect = head_intersect;

    while ((NULL != cur_a) && (NULL != cur_b))
    {
        if ((*(int *)cur_a->data) < (*(int *)cur_b->data))
        {
            cur_a = cur_a->next;
        }
        else if ((*(int *)cur_a->data) > (*(int *)cur_b->data))
        {
            cur_b = cur_b->next;
        }
        else
        {
            result = list_insert(head_intersect, cur_intersect, cur_a->data);
            if (SUCCESS != result)
            {
                error("failed to insert list!");
                return NULL;
            }

            cur_a = cur_a->next;
            cur_b = cur_b->next;
            cur_intersect = cur_intersect->next;
        }

    }

    return head_intersect;
}
