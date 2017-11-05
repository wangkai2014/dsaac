#include "utils.h"
#include "dlist.h"

static int list_data_size = 0;
static int data_is_equal(void *first, void *second);

int list_init(struct list** head, int elem_size)
{
    void *data;
    int result;
    struct list *tail = NULL;

    list_data_size = elem_size;

    data = malloc(list_data_size);
    if (NULL == data)
    {
        print_error("failed to malloc memory!");
        return MALLOC_FAIL;
    }

    memset(data, 0, list_data_size);

    result = list_create(head, data);
    if (SUCCESS != result)
    {
        print_error("failed to create head node!");
        return result;
    }

    tail = (*head)->next;
    result = list_create(&tail, data);
    if (SUCCESS != result)
    {
        print_error("failed to create tail node!");
        return result;
    }

    (*head)->prev = tail;
    tail->prev = (*head);
    tail->next = (*head);

    return SUCCESS;
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

    root->data = malloc(list_data_size);
    if (NULL == root->data)
    {
        print_error("failed to malloc memory for list's data!");
        return MALLOC_FAIL;
    }

    memcpy(root->data, data, list_data_size);
    root->prev = NULL;
    root->next = NULL;
    *head = root; 

    return SUCCESS;
}

inline int list_is_empty(struct list *head)
{
    return ((head->prev == head->next) ? TRUE : FALSE);
}

inline int list_is_first(struct list *head, struct list *cur)
{
    return ((cur == head->next) ? TRUE : FALSE);
}

inline int list_is_last(struct list *head, struct list *cur)
{
    return ((cur->next == head->prev) ? TRUE : FALSE);
}

int list_is_end(struct list *head, struct list *cur)
{
    return ((cur == head->prev) ? TRUE : FALSE);
}

struct list *list_last(struct list *head)
{
    return head->prev->prev;
}

/* return NULL if not found */
struct list *list_find(struct list *head, void *data)
{
    struct list *cur = head->next;

    if (list_is_empty(head))
    {
        print_error("list is empty!");
        return NULL;
    }

    while ((!list_is_end(head, cur)) && (!data_is_equal(cur->data, data)))
    {
        cur = cur->next;
    }

    return ((list_is_end(head, cur) ? NULL : cur));
}

/* return NULL if not found */
struct list *list_find_prev(struct list *head, void *data)
{
    struct list *prev = head;

    if (list_is_empty(head))
    {
        print_error("list is empty!");
        return NULL;
    }

    while ((!list_is_end(head, prev->next)) && (!data_is_equal(prev->next->data, data)))
    {
        prev = prev->next;
    }

    return ((list_is_end(head, prev->next) ? NULL : prev));
}

int list_push_back(struct list *head, void *data)
{
    int result;
    struct list *last = NULL;
    struct list *tail = head->prev;

    result = list_create(&last, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    last->prev = tail->prev;
    last->next = tail;
    tail->prev->next = last;
    tail->prev = last;

    return SUCCESS;
}

int list_push_front(struct list *head, void *data)
{
    int result;
    struct list *first = NULL;

    result = list_create(&first, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    first->prev = head;
    first->next = head->next;
    head->next->prev = first;
    head->next = first;

    return SUCCESS;
}

int list_pop_back(struct list *head, void *data)
{
    struct list *tail = head->prev;
    struct list *last = tail->prev;

    if (list_is_empty(head))
    {
        print_error("pop empty list!");
        return UNDERFLOW; 
    }

    tail->prev = last->prev;
    last->prev->next = tail;
    
    memcpy(data, last->data, list_data_size);

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

    head->next = first->next;
    first->next->prev = head;

    memcpy(data, first->data, list_data_size);

    free(first->data);
    free(first);
    first = NULL;

    return SUCCESS;
}

int list_insert(struct list *prev, void *data)
{
    int result;
    struct list *cur = NULL;

    result = list_create(&cur, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    cur->next = prev->next;
    cur->prev = prev;
    prev->next->prev = cur;
    prev->next = cur;

    return SUCCESS;
}

void list_del(struct list *head, struct list *cur)
{
    if (list_is_empty(head))
    {
        return;
    }

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;

    free(cur->data);
    free(cur);
    cur = NULL;
}

void list_del_by_data(struct list *head, void *data)
{
    struct list *cur;

    cur = list_find(head, data);

    if (NULL != cur)
    {
        list_del(head, cur);
    }
}

void list_clear(struct list *head)
{
    void *data;

    data = malloc(list_data_size);
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
        result = list_insert(cur_desc, cur_src->data);
        if (SUCCESS != result)
        {
            print_error("failed to insert list!");
            return result;
        }

        cur_desc = cur_desc->next;
        cur_src = cur_src->next;
    }

    result = list_insert(cur_desc, cur_src->data);
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

    result = list_init(head, sizeof(int));
    if (SUCCESS != result)
    {
        print_error("failed to initialize list!");
        return result;
    }

    for (pos = 0; pos < num; pos++)
    {
        result = list_push_back(*head, arr + pos);
        if (SUCCESS != result)
        {
            print_error("failed to pushback list!");
            return result;
        }
    }

    return SUCCESS;
}

int list_create_from_poly_arr(struct list **head, void *arr, int num)
{
    int pos;
    int result;

    result = list_init(head, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        print_error("failed to initialize list!");
        return result;
    }

    for (pos = 0; pos < num; pos++)
    {
        result = list_push_back(*head, (struct polynomial*)arr + pos);
        if (SUCCESS != result)
        {
            print_error("failed to create list!");
            return result;
        }
    }

    return SUCCESS;
}

void list_print_int(struct list *head)
{
    struct list *cur = head->next;

    while (!list_is_end(head, cur))
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }

    printf("\n");
}

void list_print_poly(struct list *head)
{
    struct list *cur = head->next;
    struct polynomial *data = NULL;

    while (!list_is_end(head, cur))
    {
        data = (struct polynomial *)cur->data;
        printf("%dx^%d ", data->coef, data->expo);
        cur = cur->next;
    }

    printf("\n");
}

static int data_is_equal(void *first, void *second)
{
    return ((memcmp((void *)first, (void *)second, list_data_size) == 0)? TRUE : FALSE);
}
