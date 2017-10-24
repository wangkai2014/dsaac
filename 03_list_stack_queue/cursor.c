#include "utils.h"
#include "cursor.h"

#define SPACE_SIZE 1000

struct node cursor_space[SPACE_SIZE];

void cursor_init()
{
    int pos = 0;

    memset(cursor_space, 0 ,sizeof(struct node) * SPACE_SIZE);

    for (pos = 0; pos < SPACE_SIZE; pos++)
    {
        cursor_space[pos].next = pos + 1;
    }
}

int list_init()
{
    int head = 0;

    head = cursor_alloc();
    if (0 == head)
    {
        printf("failed to alloc memory for head!\n");
    }
    else
    {
        cursor_space[head].data = 0;
        cursor_space[head].next = 0;
    }

    return head;
}

int list_is_empty(int head)
{
    return ((cursor_space[head].next == 0) ? TRUE : FALSE);
}

int list_is_last(int head, int cur)
{
    return ((cursor_space[cur].next == 0) ? TRUE : FALSE);
}

int data_is_equal(data_type first, data_type second)
{
    return ((first == second) ? TRUE : FALSE);
}

int list_find(int head, data_type data)
{
    int cur = cursor_space[head].next;

    while ((0 != cur) && (!data_is_equal(cursor_space[cur].data, data)))
    {
        cur = cursor_space[cur].next;
    }

    return cur;
}

int list_find_prev(int head, data_type data)
{
    int prev = head;
    int cur = cursor_space[head].next;

    while ((0 != cur) && (!data_is_equal(cursor_space[cur].data, data)))
    {
        cur = cursor_space[cur].next;
        prev = cur;
    }

    return ((0 == cur) ? 0 : prev);
}

int cursor_alloc()
{
    int pos;

    pos = cursor_space[0].next;
    cursor_space[0].next = cursor_space[pos].next;

    return pos;
}

void cursor_free(int pos)
{
    cursor_space[pos].next = cursor_space[0].next;
    cursor_space[0].next = pos;
}

int list_push_back(int head, data_type data)
{
    int prev = head;
    int pos = 0;

    pos = cursor_alloc();
    if (0 == pos)
    {
        printf("failed to alloc memory!\n");
        return MALLOC_FAIL;
    }

    while (0 != cursor_space[prev].next)
    {
        prev = cursor_space[prev].next;
    }

    cursor_space[prev].next = pos;
    cursor_space[pos].next = 0;
    cursor_space[pos].data = data;

    return SUCCESS;
}

int list_push_front(int head, data_type data)
{
    int pos = 0;

    pos = cursor_alloc();
    if (0 == pos)
    {
        printf("failed to alloc memory!\n");
        return MALLOC_FAIL;
    }

    cursor_space[pos].next = cursor_space[head].next;
    cursor_space[pos].data = data;
    cursor_space[head].next = pos;

    return SUCCESS;
}

int list_pop_back(int head)
{
    int prev = head;
    int cur = cursor_space[head].next;
    int data = 0;

    if (list_is_empty(head))
    {
        printf("cannot pop empty list!\n");
        return 0;
    }

    while (0 != cursor_space[cur].next)
    {
        prev = cur;
        cur = cursor_space[cur].next;
    }

    data = cursor_space[cur].data;
    cursor_space[prev].next = 0;

    cursor_free(cur);

    return data;
}

int list_pop_front(int head)
{
    int first = cursor_space[head].next;
    int data = 0;

    if (list_is_empty(head))
    {
        printf("cannot pop empty list!");
        return 0;
    }

    data = cursor_space[first].data;
    cursor_space[head].next = cursor_space[first].next;
    
    cursor_free(first);

    return data;
}

int list_insert(int head, int prev, data_type data)
{
    int cur = 0;

    cur = cursor_alloc();
    if (0 == cur)
    {
        printf("failed to alloc memory!\n");
        return MALLOC_FAIL;
    }

    cursor_space[cur].data = data;
    cursor_space[cur].next = cursor_space[prev].next;
    cursor_space[prev].next = cur;

    return SUCCESS;
}

void list_del(int head, data_type data)
{
    int prev = 0;
    int cur = 0;

    prev = list_find_prev(head, data);
    if (0 == prev)
    {
        printf("not found!\n");
        return;
    }

    cur = cursor_space[prev].next;
    cursor_space[prev].next = cursor_space[cur].next;

    cursor_free(cur);
}

void list_clear(int head)
{
    while (!list_is_empty(head))
    {
        list_pop_front(head);
    }
}

void list_print_int(int head)
{
    int cur = cursor_space[head].next;

    while (0 != cur)
    {
        printf("%d ", cursor_space[cur].data);

        cur = cursor_space[cur].next;
    }

    printf("\n");
}
