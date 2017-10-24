#ifndef __CURSOR_H__
#define __CURSOR_H__

typedef int data_type;

struct node
{
    data_type data;
    int next;
};

int cursor_alloc();
void cursor_free(int pos);

void cursor_init();
int list_init();
int list_is_empty(int head);
int list_is_last(int head, int cur);
int list_find(int head, data_type data);
int list_find_prev(int head, data_type data);
int list_push_back(int head, data_type data);
int list_push_front(int head, data_type data);
int list_pop_back(int head);
int list_pop_front(int head);
int list_insert(int head, int prev, data_type data);
void list_del(int head, data_type data);
void list_clear(int head);
int list_copy(int desc, int src, int elem_size);
int list_reverse(int head);

void list_print_int(int head);
#endif
