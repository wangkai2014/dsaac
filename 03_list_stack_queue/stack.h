#ifndef __STACK_H__
#define __STACK_H__

struct node
{
    void *data;
    struct node *next;
};

typedef struct node *stack;

int stack_init(stack *stck, int elem_size);
int stack_is_empty(stack stck);
int stack_push(stack stck, void *data);
int stack_pop(stack stck, void *data);
int stack_top(stack stck, void *data);
void stack_clear(stack stck);

#endif
