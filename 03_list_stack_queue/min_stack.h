/* this is the description of a special stack, which can find 
 * the smallest element in the stack in O(1) worst case time */
#ifndef __MIN_STACK_H__
#define __MIN_STACK_H__

struct node
{
    void *data;
    struct node *next;
};

struct min_stack
{
    int data_size;
    struct node *head;
    struct node *min;
};

typedef struct min_stack *stack;

int stack_init(stack *stck, int elem_size);
int stack_is_empty(stack stck);
int stack_push(stack stck, void *data);
int stack_pop(stack stck, void *data);
int stack_top(stack stck, void *data);
int stack_min(stack stck, void *data);
void stack_print(stack stck);
void stack_clear(stack *stck);

#endif
