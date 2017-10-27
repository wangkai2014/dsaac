/* use lazy deletion to implement the linked list */
#ifndef __LAZY_LIST_H__
#define __LAZY_LIST_H__

struct list
{
    char is_del;  /* marked whether the node has been deleted, 
                     0: nondeleted, 1: deleted */
    char rsv[3];  /* reserved bytes */
    void *data;
    struct list *next;
};

int list_init(struct list **head, int elem_size);
int list_create(struct list **head, void *data);
int list_is_empty(struct list *head);
int list_is_last(struct list *head, struct list *cur);
struct list* list_find(struct list *head, void *data);
struct list* list_find_prev(struct list *head, void *data);
struct list* list_find_recursively(struct list *head, void *data);
int list_push_back(struct list *head, void *data);
int list_push_front(struct list *head, void *data);
int list_pop_back(struct list *head, void *data);
int list_pop_front(struct list *head, void *data);
int list_insert(struct list *head, struct list *prev, void *data);
void list_del(struct list *head, void *data);
void list_clear(struct list *head);
int list_copy(struct list **desc, struct list *src, int elem_size);
int list_reverse(struct list *head);

int list_create_from_int_arr(struct list **head, int *arr, int num);
void list_print_int(struct list *head);

int list_create_from_poly_arr(struct list **head, void *arr, int num);
void list_print_poly(struct list *head);

int list_create_from_student_arr(struct list **head, void *arr, int num);

int data_is_equal(void *first, void *second);
#endif
