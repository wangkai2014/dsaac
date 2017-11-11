/* description of queue using array */
#ifndef __LQUEUE_H__
#define __LQUEUE_H__

#include "dlist.h"

struct node
{
    int data;
    struct node *prev;
    struct node *next;
};

struct queue_rec
{
    int size;
    struct list *head;
};

typedef struct queue_rec *queue;

int queue_init(queue *que);
int queue_is_empty(queue que);
int queue_enqueue(queue que, int elem);
int queue_dequeue(queue que, int *elem);
int queue_front(queue que, int *front);
void queue_print(queue que);
void queue_clear(queue *que);

#endif
