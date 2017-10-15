#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "dlist.h"

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
    root->prev = NULL;
    root->next = NULL;
    *head = root; 

    return SUCCESS;
}

inline int list_is_empty(struct list *head)
{
    return ((head->next == NULL) ? TRUE : FALSE);
}

inline int list_is_last(struct list *head, struct list *cur)
{
    return ((cur->next == NULL) ? TRUE : FALSE);
}

/* return NULL if not found */
struct list* list_find(struct list *head, void *data)
{
    struct list *cur = head;

    while ((NULL != cur) && (!data_is_equal(cur->data, data)))
    {
        cur = cur->next;
    }

    return cur;
}

/* return NULL if not found */
struct list* list_find_prev(struct list *head, void *data)
{
    struct list *prev = head;

    while ((NULL != prev->next) && (!data_is_equal(prev->next->data, data)))
    {
        prev = prev->next;
    }

    return ((NULL == prev->next)? NULL : prev);
}

int list_push_back(struct list *head, void *data)
{
    int result;
    struct list *last = NULL;
    struct list *cur = head;

    result = list_create(&last, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    while (NULL != cur->next)
    {
        cur = cur->next;
    }

    cur->next = last;
    last->prev = cur;

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
    head->next = first;

    return SUCCESS;
}

int list_pop_back(struct list *head, void *data)
{
    struct list *cur = head->next;

    if (list_is_empty(head))
    {
        print_error("pop empty list!");
        return UNDERFLOW; 
    }

    while (NULL != cur->next)
    {
        cur = cur->next;
    }
    
    memcpy(data, cur->data, data_size);

    cur->prev->next = NULL;
    cur->prev = NULL;
    free(cur->data);
    free(cur);
    cur = NULL;

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

    memcpy(data, first->data, data_size);

    head->next = first->next;
    first->next->prev = head;

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

    cur->prev = prev;
    cur->next = prev->next;
    prev->next->prev = cur;
    prev->next = cur;

    return SUCCESS;
}

void list_del(struct list *head, void *data)
{
    struct list *prev;
    struct list *cur;

    prev = list_find_prev(head, data);

    if (NULL == prev)
    {
        return;  /* not found */
    }

    cur = prev->next;
    prev->next = cur->next;
    cur->next->prev = prev;

    free(cur->data);
    free(cur);
    cur = NULL;
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

    while (NULL != head->next)
    {
        list_pop_front(head, data);
    }
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

        node->prev = cur;
        cur->next = node;
        cur = node;
    }

    return SUCCESS;
}

void list_print_int(struct list *head)
{
    struct list *cur = head->next;

    while (NULL != cur)
    {
        printf("%d ", *(int *)cur->data);
        cur = cur->next;
    }

    printf("\n");
}

static int data_is_equal(void *first, void *second)
{
    return ((memcmp((void *)first, (void *)second, data_size) == 0)? TRUE : FALSE);
}
