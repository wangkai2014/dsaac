/* description of queue using array */
#ifndef __AQUEUE_H__
#define __AQUEUE_H__

struct queue_rec
{
    int capacity;
    int size;
    int front;
    int rear;
    int *arr;
};

typedef struct queue_rec *queue;

int queue_init(queue *que, int capacity);
int queue_is_empty(queue que);
int queue_is_full(queue que);
int queue_enqueue(queue que, int elem);
int queue_dequeue(queue que, int *elem);
int queue_front(queue que, int *front);
void queue_print(queue que);
void queue_clear(queue *que);

#endif
