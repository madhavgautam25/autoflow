#include <stdio.h>
#include "scheduler.h"

int main() {

    Scheduler *scheduler = scheduler_create(3);

    if (scheduler == NULL) {
        printf("Failed to create scheduler.\n");
        return 1;
    }

    scheduler_add_process(scheduler, 1, 0, 50, 1);
    scheduler_add_process(scheduler, 2, 0, 1, 10);
    scheduler_add_process(scheduler, 3, 45, 1, 6);

    scheduler_run_priority(scheduler);

    printf("\nPriority Scheduling with Aging\n");
    printf("-----------------------------------------------\n");
    printf("PID\tAT\tBT\tP\tEffective P\tST\tWT\n");

    for (int i = 0; i < scheduler->process_count; i++) {

        Process *process = &scheduler->processes[i];

        printf(
            "%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
            process->pid,
            process->arrival_time,
            process->burst_time,
            process->priority,
            process->effective_priority,
            process->start_time,
            process->waiting_time
        );
    }

    printf(
        "\nPriority 10 process waits 50 units, improves by 5, "
        "and starts before the priority 6 process.\n"
    );

    scheduler_destroy(scheduler);

    return 0;
}