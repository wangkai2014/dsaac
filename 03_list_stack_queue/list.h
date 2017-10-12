#ifndef __LIST_H__
#define __LIST_H__

struct list
{
    void *data;
    struct list *next;
};

int list_init(struct list **head, int elem_size);
int list_create(struct list **head, void *data);
int list_is_empty(struct list *head);
int list_is_last(struct list *head, struct list *cur);
struct list* list_find(struct list *head, void *data);
struct list* list_find_prev(struct list *head, void *data);
int list_push_back(struct list *head, void *data);
int list_push_front(struct list *head, void *data);
int list_pop_back(struct list *head, void *data);
int list_pop_front(struct list *head, void *data);
int list_insert(struct list *head, struct list *prev, void *data);
void list_del(struct list *head, void *data);
void list_clear(struct list *head);

int list_create_from_int_arr(struct list **head, int *arr, int num);
void list_print_int(struct list *head);

int list_create_from_poly_arr(struct list **head, void *arr, int num);
void list_print_poly(struct list *head);
#endif
