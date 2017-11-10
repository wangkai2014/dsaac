#ifndef __THREE_STACK_H__
#define __THREE_STACK_H__

#define STACK_NUM   3

struct stack_info
{
    int size;
    int first_num;
    int second_num;
    int third_num;
    int third_start;
    int *arr;
};

typedef struct stack_info *stack;

int stack_init(stack *stck, int size);
int stack_is_empty(stack stck, int stck_id);
int stack_is_full(stack stck, int stck_id);
int stack_push(stack stck, int stck_id, int elem);
int stack_pop(stack stck, int stck_id, int *elem);
int stack_top(stack stck, int stck_id, int *elem);
int stack_print(stack stck);
int stack_clear(stack *stck);
#endif
