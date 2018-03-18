#include "utils.h"
#include "list.h"

static int data_is_equal(void *first, void *second, int data_size);

int list_init(List** head, int data_size)
{
    void *data;
    int result;
    List *tail = NULL;

    data = malloc(data_size);
    if (NULL == data)
    {
        ERR_MSG("failed to malloc memory!");
        return MALLOC_FAIL;
    }

    memset(data, 0, data_size);

    result = list_create(head, data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to create head node!");
        return result;
    }

    result = list_create(&tail, data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to create tail node!");
        return result;
    }

    tail->prev = (*head);
    tail->next = (*head);
    (*head)->next = tail;
    (*head)->prev = tail;

    return SUCCESS;
}

int list_create(List** head, void *data, int data_size)
{
    List *root = NULL;
    
    root = (List *)malloc(sizeof(List));
    if (NULL == root)
    {
        ERR_MSG("failed to malloc memory for list!");
        return MALLOC_FAIL;
    }

    root->data = malloc(data_size);
    if (NULL == root->data)
    {
        ERR_MSG("failed to malloc memory for list's data!");
        return MALLOC_FAIL;
    }

    memcpy(root->data, data, data_size);
    root->prev = NULL;
    root->next = NULL;
    *head = root; 

    return SUCCESS;
}

inline int list_is_empty(List *head)
{
    return ((head->prev == head->next) ? TRUE : FALSE);
}

inline int list_is_first(List *head, List *cur)
{
    return ((cur == head->next) ? TRUE : FALSE);
}

inline int list_is_last(List *head, List *cur)
{
    return ((cur->next == head->prev) ? TRUE : FALSE);
}

int list_is_end(List *head, List *cur)
{
    return ((cur == head->prev) ? TRUE : FALSE);
}

List *list_last(List *head)
{
    return head->prev->prev;
}

/* return NULL if not found */
List *list_find(List *head, void *data, int data_size)
{
    List *cur = head->next;

    if (list_is_empty(head))
    {
        ERR_MSG("list is empty!");
        return NULL;
    }

    while ((!list_is_end(head, cur)) && (!data_is_equal(cur->data, data, data_size)))
    {
        cur = cur->next;
    }

    return ((list_is_end(head, cur) ? NULL : cur));
}

/* return NULL if not found */
List *list_find_prev(List *head, void *data, int data_size)
{
    List *prev = head;

    if (list_is_empty(head))
    {
        ERR_MSG("list is empty!");
        return NULL;
    }

    while ((!list_is_end(head, prev->next)) && (!data_is_equal(prev->next->data, data, data_size)))
    {
        prev = prev->next;
    }

    return ((list_is_end(head, prev->next) ? NULL : prev));
}

int list_push_back(List *head, void *data, int data_size)
{
    int result;
    List *last = NULL;
    List *tail = head->prev;

    result = list_create(&last, data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to create list!");
        return result;
    }

    last->prev = tail->prev;
    last->next = tail;
    tail->prev->next = last;
    tail->prev = last;

    return SUCCESS;
}

int list_push_front(List *head, void *data, int data_size)
{
    int result;
    List *first = NULL;

    result = list_create(&first, data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to create list!");
        return result;
    }

    first->prev = head;
    first->next = head->next;
    head->next->prev = first;
    head->next = first;

    return SUCCESS;
}

int list_pop_back(List *head, void *data, int data_size)
{
    List *tail = head->prev;
    List *last = tail->prev;

    if (list_is_empty(head))
    {
        ERR_MSG("pop empty list!");
        return UNDERFLOW; 
    }

    tail->prev = last->prev;
    last->prev->next = tail;
    
    memcpy(data, last->data, data_size);

    free(last->data);
    free(last);
    last = NULL;

    return SUCCESS;
}

int list_pop_front(List *head, void *data, int data_size)
{
    List *first = head->next;

    if (list_is_empty(head))
    {
        ERR_MSG("pop empty list!");
        return UNDERFLOW; 
    }

    head->next = first->next;
    first->next->prev = head;

    memcpy(data, first->data, data_size);

    free(first->data);
    free(first);
    first = NULL;

    return SUCCESS;
}

int list_insert(List *prev, void *data, int data_size)
{
    int result;
    List *cur = NULL;

    result = list_create(&cur, data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to create list!");
        return result;
    }

    cur->next = prev->next;
    cur->prev = prev;
    prev->next->prev = cur;
    prev->next = cur;

    return SUCCESS;
}

void list_del(List *head, List *cur)
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

void list_del_by_data(List *head, void *data, int data_size)
{
    List *cur;

    cur = list_find(head, data, data_size);

    if (NULL != cur)
    {
        list_del(head, cur);
    }
}

void list_clear(List **head)
{
    while (!list_is_empty(*head))
    {
        list_del(*head, (*head)->next);
    }

    free((*head)->data);
    free(*head);
    *head = NULL;
}

int list_copy(List **desc, List *src, int data_size)
{
    int result = 0;
    List *cur_src = NULL;
    List *cur_desc = NULL;

    if ((NULL == desc) || (NULL == src))
    {
        ERR_MSG("null pointer!");
        return NUL_PTR;
    }

    result = list_init(desc, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to init list desc!");
        return result;
    }

    cur_src = src->next;
    cur_desc = *desc;
    
    while (!list_is_last(src, cur_src))
    {
        result = list_insert(cur_desc, cur_src->data, data_size);
        if (SUCCESS != result)
        {
            ERR_MSG("failed to insert list!");
            return result;
        }

        cur_desc = cur_desc->next;
        cur_src = cur_src->next;
    }

    result = list_insert(cur_desc, cur_src->data, data_size);
    if (SUCCESS != result)
    {
        ERR_MSG("failed to insert list!");
        return result;
    }

    return SUCCESS;
}

int list_create_from_int_arr(List **head, int *arr, int num)
{
    int pos;
    int result;

    result = list_init(head, sizeof(int));
    if (SUCCESS != result)
    {
        ERR_MSG("failed to initialize list!");
        return result;
    }

    for (pos = 0; pos < num; pos++)
    {
        result = list_push_back(*head, arr + pos, sizeof(int));
        if (SUCCESS != result)
        {
            ERR_MSG("failed to pushback list!");
            return result;
        }
    }

    return SUCCESS;
}

int list_create_from_poly_arr(List **head, void *arr, int num)
{
    int pos;
    int result;

    result = list_init(head, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        ERR_MSG("failed to initialize list!");
        return result;
    }

    for (pos = 0; pos < num; pos++)
    {
        result = list_push_back(*head, (struct polynomial*)arr + pos, sizeof(struct polynomial));
        if (SUCCESS != result)
        {
            ERR_MSG("failed to create list!");
            return result;
        }
    }

    return SUCCESS;
}

void list_print_int(List *head)
{
    List *cur = head->next;

    while (!list_is_end(head, cur))
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }

    printf("\n");
}

void list_print_poly(List *head)
{
    List *cur = head->next;
    struct polynomial *data = NULL;

    while (!list_is_end(head, cur))
    {
        data = (struct polynomial *)cur->data;
        printf("%dx^%d ", data->coef, data->expo);
        cur = cur->next;
    }

    printf("\n");
}

static int data_is_equal(void *first, void *second, int data_size)
{
    return ((memcmp((void *)first, (void *)second, data_size) == 0)? TRUE : FALSE);
}
