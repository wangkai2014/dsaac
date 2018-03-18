/* double linked list */
#ifndef __LIST_H__
#define __LIST_H__

struct list
{
    void *data;
    struct list *prev;
    struct list *next;
};

typedef struct list List;

int list_init(List **head, int data_size);
int list_create(List **head, void *data, int data_size);
int list_is_empty(List *head);
int list_is_first(List *head, List *cur);
int list_is_last(List *head, List *cur);
int list_is_end(List *head, List *cur);
List *list_last(List *head);
List *list_find(List *head, void *data, int data_size);
List *list_find_prev(List *head, void *data, int data_size);
int list_push_back(List *head, void *data, int data_size);
int list_push_front(List *head, void *data, int data_size);
int list_pop_back(List *head, void *data, int data_size);
int list_pop_front(List *head, void *data, int data_size);
int list_insert(List *prev, void *data, int data_size);
void list_del(List *head, List *cur);
void list_del_by_data(List *head, void *data, int data_size);
void list_clear(List **head);
int list_copy(List **desc, List *src, int data_size);

int list_create_from_int_arr(List **head, int *arr, int num);
void list_print_int(List *head);

int list_create_from_poly_arr(List **head, void *arr, int num);
void list_print_poly(List *head);
#endif
