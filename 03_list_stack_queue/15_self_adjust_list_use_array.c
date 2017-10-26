#include "utils.h"

#define MAX_ELEM_NUM 100

struct list 
{
    int size;
    int data[MAX_ELEM_NUM];
};

int list_init(struct list **lst);
int list_insert(struct list *lst, int elem);
int find(struct list *lst, int pos, int *elem);
void list_clear(struct list *lst);
void list_print(struct list *lst);

int main()
{
    int result = SUCCESS;
    int pos = 0;
    int index = 0;
    int elem = 0;
    int arr[10];
    struct list *lst = NULL;

    result = list_init(&lst);
    if (SUCCESS != result)
    {
        printf("failed to init list!\n");
        return 0;
    }

    for (pos = 0; pos < 10; pos++)
    {
        arr[pos] = pos * (pos + 2);

        result = list_insert(lst, arr[pos]);
        if (SUCCESS != result)
        {
            printf("failed to insert list!\n");
            return 0;
        }
    }

    printf("At the beginning, the list is :\n");
    list_print(lst);

    srand(time(NULL));

    for (pos = 0; pos < 10; pos++)
    {
        index = rand() % 10;

        result = find(lst, index, &elem);
        if (SUCCESS != result)
        {
            printf("failed to find the No.%d element in the list!\n", index);
            return 0;
        }

        printf("After finding the No.%d element %d, the list is:\n", index, elem);
        list_print(lst);
    }

    list_clear(lst);

    return 0;
}

int list_init(struct list **lst)
{
    struct list *cur = NULL;

    cur = (struct list *)malloc(sizeof(struct list));
    if (NULL == cur)
    {
        printf("failed to malloc memory for cur list!\n");
        return MALLOC_FAIL;
    }

    memset(cur, 0, sizeof(struct list));

    *lst = cur;

    return SUCCESS;
}

int list_insert(struct list *lst, int elem)
{
    int pos = 0;

    if (NULL == lst)
    {
        printf("null pointer!\n");
        return NUL_PTR;
    }

    if (lst->size >= MAX_ELEM_NUM)
    {
        printf("the list is full!\n");
        return OVERFLOW;
    }

    for (pos = lst->size; pos > 0; pos--)
    {
        lst->data[pos] = lst->data[pos-1];
    }

    lst->data[0] = elem;
    lst->size++;

    return SUCCESS;
}

int find(struct list *lst, int pos, int *elem)
{
    int data = 0;
    int index = 0;

    if ((NULL == lst) || (NULL == elem))
    {
        printf("null pointer!\n");
        return NUL_PTR;
    }

    if ((pos < 0 ) || (pos >= lst->size))
    {
        printf("invalid pos[%d]!\n", pos);
        return INVALID_INPUT;
    }

    data = lst->data[pos];

    for (index = pos; index > 0; index--)
    {
        lst->data[index] = lst->data[index-1];
    }

    lst->data[0] = data;
    *elem = data;

    return SUCCESS;
}

void list_clear(struct list *lst)
{
    if (NULL != lst)
    {
        free(lst);
    }
}
void list_print(struct list *lst)
{
    int pos = 0;

    if (NULL == lst)
    {
        printf("null pointer!\n");
        return;
    }

    for (pos = 0; pos < lst->size; pos++)
    {
        printf("%d ", lst->data[pos]);
    }

    printf("\n");
}
