#include <stdio.h>

#include "autoflow.h"

int main() {

    Scheduler *scheduler =
        scheduler_create(2);

    if (scheduler == NULL) {
        printf("Failed to create scheduler.\n");
        return 1;
    }

    scheduler_add_process(scheduler, 1, 0, 20, 2);
    scheduler_add_process(scheduler, 2, 0, 4, 1);

    int quantum =
        workload_adaptive_quantum(
            scheduler->processes,
            scheduler->process_count
        );

    printf("\nAutoFlow Adaptive Scheduling\n");
    printf("--------------------------------\n");
    printf("Initial adaptive time quantum: %d\n", quantum);

    scheduler->processes[0].remaining_time -= quantum;

    int next_quantum =
        workload_adaptive_quantum_remaining(
            scheduler->processes,
            scheduler->process_count
        );

    printf(
        "After PID 1 uses one %d-unit slice, the next quantum is: %d\n",
        quantum,
        next_quantum
    );

    scheduler->processes[0].remaining_time =
        scheduler->processes[0].burst_time;

    scheduler_run_adaptive(scheduler);

    printf("\nScheduling Results\n");
    printf("-----------------------------------------------\n");
    printf("PID\tAT\tBT\tST\tCT\tWT\tTAT\tRT\n");

    for (int i = 0;
         i < scheduler->process_count;
         i++) {

        Process *process =
            &scheduler->processes[i];

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