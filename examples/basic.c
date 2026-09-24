#include <stdio.h>
#include "scheduler.h"

int main() {

    Scheduler *scheduler = scheduler_create(10);

    if (scheduler == NULL) {
        printf("Failed to create scheduler.\n");
        return 1;
    }

    scheduler_add_process(scheduler, 1, 0, 8, 2);
    scheduler_add_process(scheduler, 2, 1, 3, 1);
    scheduler_add_process(scheduler, 3, 2, 12, 3);
    scheduler_add_process(scheduler, 4, 3, 2, 2);

    scheduler_print_processes(scheduler);

    scheduler_destroy(scheduler);

    return 0;
    
}