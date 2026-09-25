#include <stdio.h>

#include "scheduler.h"

int main() {

    Scheduler *scheduler = scheduler_create(4);

    if (scheduler == NULL) {
        printf("Failed to create scheduler.\n");
        return 1;
    }

    scheduler_add_process(scheduler, 1, 0, 8, 2);
    scheduler_add_process(scheduler, 2, 1, 3, 1);
    scheduler_add_process(scheduler, 3, 2, 12, 3);
    scheduler_add_process(scheduler, 4, 3, 2, 2);

    scheduler_run_sjf(scheduler);

    printf("\nSJF Results\n");
    printf("-----------------------------------------------\n");
    printf("PID\tAT\tBT\tST\tCT\tWT\tTAT\tRT\n");

    for (int i = 0; i < scheduler->process_count; i++) {

        Process *process = &scheduler->processes[i];

        printf(
            "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            process->pid,
            process->arrival_time,
            process->burst_time,
            process->start_time,
            process->completion_time,
            process->waiting_time,
            process->turnaround_time,
            process->response_time
        );
    }

    scheduler_destroy(scheduler);

    return 0;
}