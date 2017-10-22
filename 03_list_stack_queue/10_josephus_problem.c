#include "utils.h"
#include "clist.h"

int play_josephus_game(int people_num, int interval);
int list_delete_by_josephus_order(struct list *head, int interval);

int main()
{
    char go_on = 'y';
    int people_num = 0;
    int interval = 0;

    while (go_on == 'y')
    {
        printf("Enter people's number: ");
        scanf("%d", &people_num);

        printf("Enter interval: ");
        scanf("%d", &interval);

        play_josephus_game(people_num, interval);

        printf("Whether to continue?( 'y' or 'n') ");
        scanf(" %c", &go_on);
    }
}

int play_josephus_game(int people_num, int interval)
{
    int *peoples = NULL;
    int id = 0;
    int result = SUCCESS;
    struct list *head = NULL;

    peoples = (int *)malloc(sizeof(int) * people_num);
    if (NULL == peoples)
    {
        print_error("failed to malloc memory for peoples!");
        return MALLOC_FAIL;
    }

    for (id = 0; id < people_num; id++)
    {
        peoples[id] = id + 1;
    }

    result = list_create_from_int_arr(&head, peoples, people_num);
    if (SUCCESS != result)
    {
        print_error("failed to create from int array!");
        return result;
    }

    result = list_delete_by_josephus_order(head, interval);
    if (SUCCESS != result)
    {
        print_error("failed to delete list in josephus order!");
        return result;
    }

    return SUCCESS;
}

int list_delete_by_josephus_order(struct list *head, int interval)
{
    struct list *prev = head->next;
    int pass_time = 0;
    int people = 0;

    while (!list_is_last(head, prev))
    {
        prev = prev->next;
    }

    while (!list_is_empty(head))
    {
        for (pass_time = 0; pass_time < interval; pass_time++)
        {
            prev = prev->next;
        }

        people = *(int *)prev->next->data;

        list_del(head, prev);

        printf("%d ", people);
    }

    printf("\nwinner: %d\n", people);

    return SUCCESS;
}
