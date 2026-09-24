#include <stdio.h>
#include "queue.h"

int main() {

    Process p1 = {1, 0, 8, 8, 2, -1, -1, 0, 0, -1};
    Process p2 = {2, 1, 3, 3, 1, -1, -1, 0, 0, -1};
    Process p3 = {3, 2, 5, 5, 3, -1, -1, 0, 0, -1};

    ProcessQueue *queue = queue_create(3);

    if (queue == NULL) {
        printf("Failed to create queue.\n");
        return 1;
    }

    printf("Enqueue P1: %d\n", queue_enqueue(queue, &p1));
    printf("Enqueue P2: %d\n", queue_enqueue(queue, &p2));
    printf("Enqueue P3: %d\n", queue_enqueue(queue, &p3));

    printf("Queue size: %d\n", queue_size(queue));

    Process *process = queue_dequeue(queue);

    if (process != NULL) {
        printf("Dequeued: P%d\n", process->pid);
    }

    printf("Queue size: %d\n", queue_size(queue));

    queue_destroy(queue);

    printf("Is empty: %d\n", queue_is_empty(queue));
    printf("Is full: %d\n", queue_is_full(queue));

    printf("Enqueue P1 again: %d\n", queue_enqueue(queue, &p1));

    printf("Queue size: %d\n", queue_size(queue));

    return 0;
}