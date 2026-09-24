#ifndef QUEUE_H
#define QUEUE_H
#include "process.h"

typedef struct {
    Process **items;
    int front;
    int rear;
    int size;
    int capacity;
} ProcessQueue;

ProcessQueue *queue_create(int capacity);

void queue_destroy(ProcessQueue *queue);

int queue_enqueue(ProcessQueue *queue, Process *process);

Process *queue_dequeue(ProcessQueue *queue);

int queue_is_empty(ProcessQueue *queue);

int queue_is_full(ProcessQueue *queue);

int queue_size(ProcessQueue *queue);

#endif