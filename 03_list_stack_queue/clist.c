#include "utils.h"
#include "clist.h"

static int data_size = 0;
static int data_is_equal(void *first, void *second);

int list_init(struct list** head, int elem_size)
{
    void *data;

    data_size = elem_size;

    data = malloc(data_size);
    if (NULL == data)
    {
        print_error("failed to malloc memory!");
        return MALLOC_FAIL;
    }

    memset(data, 0, data_size);

    return list_create(head, data);
}

int list_create(struct list** head, void *data)
{
    struct list *root = NULL;
    
    root = (struct list *)malloc(sizeof(struct list));
    if (NULL == root)
    {
        print_error("failed to malloc memory for list!");
        return MALLOC_FAIL;
    }

    root->data = malloc(data_size);
    if (NULL == root->data)
    {
        print_error("failed to malloc memory for list's data!");
        return MALLOC_FAIL;
    }

    memcpy(root->data, data, data_size);
    root->next = NULL;
    *head = root; 

    return SUCCESS;
}

inline int list_is_empty(struct list *head)
{
    return ((NULL == head->next) ? TRUE : FALSE);
}

inline int list_is_last(struct list *head, struct list *cur)
{
    return ((cur->next == head->next) ? TRUE : FALSE);
}

inline int list_is_first(struct list *head, struct list *cur)
{
    return ((cur == head->next) ? TRUE : FALSE);
}

/* return NULL if not found */
struct list* list_find(struct list *head, void *data)
{
    struct list *cur = head->next;

    if (list_is_empty(head))
    {
        print_error("list is empty!");
        return NULL;
    }

    while ((!list_is_last(head, cur)) && (!data_is_equal(cur->data, data)))
    {
        cur = cur->next;
    }

    return (data_is_equal(cur->data, data) ? cur : NULL);
}

/* return NULL if not found */
struct list* list_find_prev(struct list *head, void *data)
{
    struct list *prev = head;

    if (list_is_empty(head))
    {
        print_error("list is empty!");
        return NULL;
    }

    while ((!list_is_last(head, prev->next)) && (!data_is_equal(prev->next->data, data)))
    {
        prev = prev->next;
    }

    return (data_is_equal(prev->next->data, data)? prev : NULL);
}

int list_push_back(struct list *head, void *data)
{
    int result;
    struct list *last = NULL;
    struct list *cur = head->next;

    result = list_create(&last, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    if (list_is_empty(head))
    {
        head->next = last;
        last->next = last;
        return SUCCESS;
    }

    while (!list_is_last(head, cur))
    {
        cur = cur->next;
    }

    cur->next = last;
    last->next = head->next;

    return SUCCESS;
}

int list_push_front(struct list *head, void *data)
{
    int result;
    struct list *first = NULL;
    struct list *cur = head->next;

    result = list_create(&first, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    if (list_is_empty(head))
    {
        head->next = first;
        first->next = first;
        return SUCCESS;
    }
    
    while (!list_is_last(head, cur))
    {
        cur = cur->next;
    }

    cur->next = first;
    first->next = head->next;
    head->next = first;

    return SUCCESS;
}

int list_pop_back(struct list *head, void *data)
{
    struct list *prev = head;
    struct list *last = NULL;

    if (list_is_empty(head))
    {
        print_error("pop empty list!");
        return UNDERFLOW; 
    }

    while (!list_is_last(head, prev->next))
    {
        prev = prev->next;
    }
    
    last = prev->next;
    
    if (list_is_last(head, head->next)) /* only one node in the list */
    {
        head->next = NULL;
    }
    else
    {
        prev->next = head->next;
    }

    memcpy(data, last->data, data_size);

    free(last->data);
    free(last);
    last = NULL;

    return SUCCESS;
}

int list_pop_front(struct list *head, void *data)
{
    struct list *first = head->next;

    if (list_is_empty(head))
    {
        print_error("pop empty list!");
        return UNDERFLOW; 
    }

    if (list_is_last(head, first)) /* only one node in the list */
    {
        head->next = NULL;
    }
    else
    {
        head->next = first->next;
    }

    memcpy(data, first->data, data_size);

    free(first->data);
    free(first);
    first = NULL;

    return SUCCESS;
}

int list_insert(struct list *head, struct list *prev, void *data)
{
    int result;
    struct list *cur = NULL;

    result = list_create(&cur, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    if (list_is_empty(head))
    {
        cur->next = cur;
        head->next = cur;
    }
    else
    {
        cur->next = prev->next;
        prev->next = cur;
    }

    return SUCCESS;
}

void list_del(struct list *head, struct list *prev)
{
    struct list *cur = prev->next;

    if (cur->next == cur) /* only one node in the list */
    {
        head->next = NULL;
    }
    else if (list_is_first(head, cur))  /* delete first node in the list */
    {
        head->next = cur->next;
    }

    prev->next = cur->next;

    free(cur->data);
    free(cur);
    cur = NULL;
}

void list_del_by_data(struct list *head, void *data)
{
    struct list *prev;

    prev = list_find_prev(head, data);

    if (NULL != prev)  
    {
        list_del(head, prev);
    }
}

void list_clear(struct list *head)
{
    void *data;

    data = malloc(data_size);
    if (NULL == data)
    {
        print_error("failed to malloc memory for list's data.");
        return;
    }

    while (!list_is_empty(head))
    {
        list_pop_front(head, data);
    }
}

int list_copy(struct list **desc, struct list *src, int elem_size)
{
    int result = 0;
    struct list *cur_src = NULL;
    struct list *cur_desc = NULL;

    if ((NULL == desc) || (NULL == src))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    result = list_init(desc, elem_size);
    if (SUCCESS != result)
    {
        print_error("failed to init list desc!");
        return result;
    }

    cur_src = src->next;
    cur_desc = *desc;
    
    while (!list_is_last(src, cur_src))
    {
        result = list_insert(*desc, cur_desc, cur_src->data);
        if (SUCCESS != result)
        {
            print_error("failed to insert list!");
            return result;
        }

        cur_desc = cur_desc->next;
        cur_src = cur_src->next;
    }

    result = list_insert(*desc, cur_desc, cur_src->data);
    if (SUCCESS != result)
    {
        print_error("failed to insert list!");
        return result;
    }

    return SUCCESS;
}

int list_create_from_int_arr(struct list **head, int *arr, int num)
{
    int pos;
    int result;
    struct list *node = NULL;
    struct list *cur = NULL;

    result = list_init(head, sizeof(int));
    if (SUCCESS != result)
    {
        print_error("failed to initialize list!");
        return result;
    }

    cur = *head;

    for (pos = 0; pos < num; pos++)
    {
        result = list_create(&node, arr + pos);
        if (SUCCESS != result)
        {
            print_error("failed to create list!");
            return result;
        }

        cur->next = node;
        node->next = (*head)->next;
        cur = node;
    }

    return SUCCESS;
}

int list_create_from_poly_arr(struct list **head, void *arr, int num)
{
    int pos;
    int result;
    struct list *node = NULL;
    struct list *cur = NULL;

    result = list_init(head, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        print_error("failed to initialize list!");
        return result;
    }

    cur = *head;

    for (pos = 0; pos < num; pos++)
    {
        result = list_create(&node, (struct polynomial*)arr + pos);
        if (SUCCESS != result)
        {
            print_error("failed to create list!");
            return result;
        }

        cur->next = node;
        node->next = (*head)->next;
        cur = node;
    }

    return SUCCESS;
}

void list_print_int(struct list *head)
{
    struct list *cur = head->next;

    while (!list_is_last(head, cur))
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }

    printf("%d\n", *(int *)cur->data);
}

void list_print_poly(struct list *head)
{
    struct list *cur = head->next;
    struct polynomial *data = NULL;

    while (!list_is_last(head, cur))
    {
        data = (struct polynomial *)cur->data;
        printf("%dx^%d ", data->coef, data->expo);
        cur = cur->next;

        if (head != cur)
        {
            printf("+ ");
        }
    }

    printf("%dx^%d\n", data->coef, data->expo);
}

static int data_is_equal(void *first, void *second)
{
    return ((memcmp((void *)first, (void *)second, data_size) == 0)? TRUE : FALSE);
}
