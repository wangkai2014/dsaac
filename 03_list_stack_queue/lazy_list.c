/* use lazy deletion to implement the linked list */
#include "utils.h"
#include "lazy_list.h"

static int data_size = 0;
static int del_num = 0;
static int nondel_num = 0;

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
    root->is_del = FALSE;
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

struct list* list_find_recursively(struct list *head, void *data)
{
    if (NULL == head)
    {
        return NULL;
    }
    else if (data_is_equal(head->data, data))
    {
        return head;
    }
    else
    {
        return list_find_recursively(head->next, data);
    }
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
    nondel_num++;

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

    first->next = head->next;
    head->next = first;
    nondel_num++;

    return SUCCESS;
}

int list_pop_back(struct list *head, void *data)
{
    struct list *prev = head;

    if (list_is_empty(head))
    {
        print_error("pop empty list!");
        return UNDERFLOW; 
    }

    while (NULL != prev->next->next)
    {
        prev = prev->next;
    }
    
    memcpy(data, prev->next->data, data_size);

    free(prev->next->data);
    free(prev->next);
    prev->next = NULL;
    nondel_num--;

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
    memcpy(data, first->data, data_size);

    free(first->data);
    free(first);
    first = NULL;
    nondel_num--;

    return SUCCESS;
}

int list_insert(struct list *head, struct list *prev, void *data)
{
    int result;
    struct list *cur = NULL;

    if (data_is_equal(prev->next->data, data))
    {
        if (prev->next->is_del)
        {
            prev->next->is_del = FALSE;
            del_num--;
            nondel_num++;
        }
        
        return SUCCESS;
    }

    result = list_create(&cur, data);
    if (SUCCESS != result)
    {
        print_error("failed to create list!");
        return result;
    }

    cur->next = prev->next;
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
    if (cur->is_del)
    {
        return;
    }
    else 
    {
        cur->is_del = TRUE;
        del_num++;
        nondel_num--;
    }
    
    if (del_num < nondel_num)
    {
        return;
    }

    prev = head;
    cur = head->next;
    while (NULL != cur)
    {
        if (cur->is_del)
        {
            prev->next = cur->next;
            free(cur->data);
            free(cur);
            del_num--;
            cur = prev->next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
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

    while (NULL != head->next)
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
    
    while (NULL != cur_src)
    {
        result = list_insert(*desc, cur_desc, cur_src->data);
        if (SUCCESS != result)
        {
            print_error("failed to insert list!");
            return result;
        }

        cur_desc = cur_desc->next;
        cur_src = cur_src->next;
        nondel_num++;
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

        nondel_num++;
        cur->next = node;
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

        nondel_num++;
        cur->next = node;
        cur = node;
    }

    return SUCCESS;
}

int list_create_from_student_arr(struct list **head, void *arr, int num)
{
    int pos;
    int result;
    struct list *node = NULL;
    struct list *cur = NULL;

    result = list_init(head, sizeof(struct student));
    if (SUCCESS != result)
    {
        print_error("failed to initialize list!");
        return result;
    }

    cur = *head;

    for (pos = 0; pos < num; pos++)
    {
        result = list_create(&node, (struct student*)arr + pos);
        if (SUCCESS != result)
        {
            print_error("failed to create list!");
            return result;
        }

        nondel_num++;
        cur->next = node;
        cur = node;
    }

    return SUCCESS;
}

void list_print_int(struct list *head)
{
    struct list *cur = head->next;
    char flag[2][4] = {"non", "del"};

    while (NULL != cur)
    {
        printf("%d(%s) ", *(int *)cur->data, flag[(int)(cur->is_del)]);
        cur = cur->next;
    }

    printf("\n");
}

void list_print_poly(struct list *head)
{
    struct list *cur = head->next;
    struct polynomial *data = NULL;

    while (NULL != cur)
    {
        data = (struct polynomial *)cur->data;
        printf("%dx^%d ", data->coef, data->expo);
        cur = cur->next;

        if (NULL != cur)
        {
            printf("+ ");
        }
    }

    printf("\n");
}

int data_is_equal(void *first, void *second)
{
    return ((memcmp((void *)first, (void *)second, data_size) == 0)? TRUE : FALSE);
}

int list_reverse(struct list *head)
{
    int result = SUCCESS;
    struct list *prev = head->next;
    struct list *cur = NULL;   /* the node need to be deleted */

    if ((NULL == prev) || (NULL == prev->next)) /* zero or one node in the list */
    {
        return SUCCESS;
    }

    cur = prev->next;

    while (NULL != cur)
    {
        prev->next = cur->next;   /* delete cur node */
        cur->next = head->next;   /* insert cur node to the front of the list */
        head->next = cur;
        cur = prev->next;
    }

    return SUCCESS;
}
