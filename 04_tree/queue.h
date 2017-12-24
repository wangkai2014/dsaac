/* description of queue using array */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "list.h"

struct queue
{
    int size;
    struct list *head;
};

typedef struct queue Queue;

int queue_init(Queue **queue);
int queue_is_empty(Queue *queue);
int queue_enqueue(Queue *queue, void *data, int data_size);
int queue_dequeue(Queue *queue, void *data, int data_size);
int queue_front(Queue *queue, void *front, int data_size);
void queue_print(Queue *queue);
void queue_clear(Queue **queue);

#endif
