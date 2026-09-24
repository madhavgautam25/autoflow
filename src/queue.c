#include <stdlib.h>
#include "queue.h"

ProcessQueue *queue_create(int capacity) {

    ProcessQueue *queue = malloc(sizeof(ProcessQueue));

    if (queue == NULL) {
        return NULL;
    }

    queue->items = malloc(sizeof(Process *) * capacity);

    if (queue->items == NULL) {
        free(queue);
        return NULL;
    }

    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;

    return queue;
}

int queue_is_empty(ProcessQueue *queue) {

    if (queue == NULL) {
        return 1;
    }

    return queue->size == 0;
}

int queue_is_full(ProcessQueue *queue) {

    if (queue == NULL) {
        return 1;
    }

    return queue->size == queue->capacity;
}

int queue_enqueue(ProcessQueue *queue, Process *process) {

    if (queue == NULL || process == NULL) {
        return 0;
    }

    if (queue_is_full(queue)){
        return 0;
    }

    queue->items[queue -> rear] = process;

    queue->rear++;
    queue->size++;

    return 1;
}

Process *queue_dequeue(ProcessQueue *queue) {

    if (queue == NULL || queue_is_empty(queue)) {
        return NULL;
    }

    Process *process = queue->items[queue->front];

    queue->front++;
    queue->size--;

    return process;
}

void queue_destroy(ProcessQueue *queue) {

    if (queue == NULL) {
        return;
    }

    free(queue->items);
    free(queue);
}

int queue_size(ProcessQueue *queue) {

    if (queue == NULL) {
        return 0;
    }

    return queue->size;
}