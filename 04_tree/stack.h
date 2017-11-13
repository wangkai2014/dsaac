#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack Stack;

struct Stack
{
    void *data;
    Stack *next;
};

int stack_init(Stack **stck, int data_size);
int stack_is_empty(Stack *stck);
int stack_push(Stack *stck, void *data, int data_size);
int stack_pop(Stack *stck, void *data, int data_size);
int stack_top(Stack *stck, void *data, int data_size);
void stack_clear(Stack **stck);

#endif
