#ifndef __TWO_STACK_H__
#define __TWO_STACK_H__

#define STACK_NUM   2

struct stack_info
{
    int size;
    int first_num;
    int second_num;
    int *arr;
};

typedef struct stack_info *stack;

int stack_init(stack *stck, int size);
int stack_push(stack stck, int stck_id, int elem);
int stack_pop(stack stck, int stck_id, int *elem);
int stack_top(stack stck, int stck_id, int *elem);
int stack_print(stack stck, int stck_id);
int stack_clear(stack stck);
#endif
