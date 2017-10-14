#include "utils.h"
#include "list.h"

void print_lots(struct list *head_l, struct list *head_p);

int main()
{
    struct list *head_l = NULL;
    struct list *head_p = NULL;
    int arr_l[10];
    int arr_p[] = {1,3,4,6,7,11,13};
    int result;
    int pos;

    for (pos = 0; pos < 10; pos++)
    {
        arr_l[pos] = pos * pos * pos;
    }

    result = list_create_from_int_arr(&head_l, arr_l, 10);
    if (SUCCESS != result)
    {
        error("failed to create list l!");
        return 0;
    }

    result = list_create_from_int_arr(&head_p, arr_p, sizeof(arr_p) / sizeof(int));
    if (SUCCESS != result)
    {
        error("failed to create list p!");
        return 0;
    }

    print_lots(head_l, head_p);
    
    return 0;
}

void print_lots(struct list *head_l, struct list *head_p)
{
    struct list *cur_l = head_l->next;
    struct list *cur_p = head_p->next;
    int last_pos = 0;
    int cur_pos = 0;

    if ((NULL == head_l) || (NULL == head_p))
    {
        error("null pointer!");
        return;
    }

    while (NULL != cur_p)
    {
        cur_pos = *(int *)cur_p->data;

        while ((NULL != cur_l) && (last_pos != cur_pos))
        {
            cur_l = cur_l->next;
            last_pos++;
        }

        if (NULL == cur_l)
        {
            break;
        }

        printf("%d ", *(int *)cur_l->data);

        cur_p = cur_p->next;
    }

    printf("\n");
}
