#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include "metrics.h"
#include "queue.h"
#include "workload.h"

Scheduler *scheduler_create(int capacity) {

    Scheduler *scheduler = malloc(sizeof(Scheduler));

    if (scheduler == NULL) {
        return NULL;
    }

    scheduler->processes = malloc(sizeof(Process) * capacity);

    if (scheduler->processes == NULL) {
        free(scheduler);
        return NULL;
    }

    scheduler->process_count = 0;
    scheduler->capacity = capacity;
    scheduler->current_time = 0;

    return scheduler;
}

int scheduler_add_process(
    Scheduler *scheduler,
    int pid,
    int arrival_time,
    int burst_time,
    int priority
) {

    if (scheduler == NULL) {
        return 0;
    }

    if (scheduler->process_count >= scheduler->capacity) {
        return 0;
    }

    Process *process = &scheduler->processes[scheduler->process_count];

    process->pid = pid;
    process->arrival_time = arrival_time;
    process->burst_time = burst_time;
    process->remaining_time = burst_time;
    process->priority = priority;
    process->effective_priority = priority;

    process->start_time = -1;
    process->completion_time = -1;
    process->waiting_time = 0;
    process->turnaround_time = 0;
    process->response_time = -1;

    scheduler->process_count++;

    return 1;
}

void scheduler_print_processes(Scheduler *scheduler) {

    if (scheduler == NULL) {
        return;
    }

    printf("\nAutoFlow Processes\n");
    printf("-----------------------------\n");

    printf("PID\tArrival\tBurst\tPriority\n");

    for (int i = 0; i < scheduler->process_count; i++) {

        Process *process = &scheduler->processes[i];

        printf(
            "%d\t%d\t%d\t%d\n",
            process->pid,
            process->arrival_time,
            process->burst_time,
            process->priority
        );
    }
}

void scheduler_destroy(Scheduler *scheduler) {

    if (scheduler == NULL) {
        return;
    }

    free(scheduler->processes);
    free(scheduler);
}

void scheduler_run_fcfs(Scheduler *scheduler) {

    if (scheduler == NULL) {
        return;
    }

    scheduler->current_time = 0;

    for (int i = 0; i < scheduler->process_count; i++) {

        Process *process = &scheduler->processes[i];

        if (scheduler->current_time < process->arrival_time) {
            scheduler->current_time = process->arrival_time;
        }

        process->start_time = scheduler->current_time;

        scheduler->current_time += process->burst_time;

        process->completion_time = scheduler->current_time;

        calculate_process_metrics(process);

    }
}

void scheduler_run_sjf(Scheduler *scheduler) {

    if (scheduler == NULL) {
        return;
    }

    int completed[scheduler->process_count];

    for (int i = 0; i < scheduler->process_count; i++) {
        completed[i] = 0;
    }

    scheduler->current_time = 0;

    int completed_count = 0;

    while (completed_count < scheduler->process_count) {

        int shortest_index = -1;

        for (int i = 0; i < scheduler->process_count; i++) {

            Process *process = &scheduler->processes[i];

            if (completed[i] == 0 && process->arrival_time <= scheduler->current_time) {

                if (shortest_index == -1 || process->burst_time < scheduler->processes[shortest_index].burst_time) {
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            scheduler->current_time++;
            continue;
        }

        Process *process = &scheduler->processes[shortest_index];

        process->start_time = scheduler->current_time;

        scheduler->current_time += process->burst_time;

        process->completion_time = scheduler->current_time;

        calculate_process_metrics(process);

        completed[shortest_index] = 1;

        completed_count++;

    }
}

void scheduler_run_priority(Scheduler *scheduler) {

    if (scheduler == NULL) {
        return;
    }

    int completed[scheduler->process_count];

    for (int i = 0; i < scheduler->process_count; i++) {
        completed[i] = 0;
    }

    scheduler->current_time = 0;

    int completed_count = 0;

    for (int i = 0; i < scheduler->process_count; i++) {
        scheduler->processes[i].effective_priority =
            scheduler->processes[i].priority;
    }

    while (completed_count < scheduler->process_count) {

        int highest_index = -1;

        for (int i = 0; i < scheduler->process_count; i++) {

            Process *process = &scheduler->processes[i];

            if (completed[i] == 0 &&
                process->arrival_time <= scheduler->current_time) {

                int waiting_time =
                    scheduler->current_time - process->arrival_time;

                process->effective_priority =
                    process->priority - waiting_time / 10;

                if (highest_index == -1 ||
                    process->effective_priority <
                    scheduler->processes[highest_index].effective_priority) {

                    highest_index = i;
                }
            }
        }

        if (highest_index == -1) {
            scheduler->current_time++;
            continue;
        }

        Process *process =
            &scheduler->processes[highest_index];

        process->start_time = scheduler->current_time;

        scheduler->current_time += process->burst_time;

        process->completion_time =
            scheduler->current_time;

        calculate_process_metrics(process);

        completed[highest_index] = 1;

        completed_count++;
    }
}


static void scheduler_run_round_robin_internal(
    Scheduler *scheduler,
    int time_quantum,
    int adaptive
) {

    if (scheduler == NULL ||
        (adaptive == 0 && time_quantum <= 0)) {
        return;
    }

    ProcessQueue *queue =
        queue_create(scheduler->process_count);

    if (queue == NULL) {
        return;
    }

    scheduler->current_time = 0;

    int completed_count = 0;

    for (int i = 0; i < scheduler->process_count; i++) {

        scheduler->processes[i].remaining_time =
            scheduler->processes[i].burst_time;

        scheduler->processes[i].start_time = -1;
        scheduler->processes[i].completion_time = -1;
    }

    if (adaptive != 0) {
        time_quantum = workload_adaptive_quantum(
            scheduler->processes,
            scheduler->process_count
        );
    }

    int added[scheduler->process_count];

    for (int i = 0; i < scheduler->process_count; i++) {
        added[i] = 0;
    }

    while (completed_count < scheduler->process_count) {

        for (int i = 0; i < scheduler->process_count; i++) {

            Process *process =
                &scheduler->processes[i];

            if (added[i] == 0 &&
                process->arrival_time <=
                    scheduler->current_time) {

                queue_enqueue(queue, process);

                added[i] = 1;
            }
        }

        if (queue_is_empty(queue)) {

            scheduler->current_time++;

            continue;
        }

        Process *process =
            queue_dequeue(queue);

        if (process == NULL) {
            continue;
        }

        if (process->start_time == -1) {

            process->start_time =
                scheduler->current_time;
        }

        int execution_time =
            time_quantum;

        if (process->remaining_time <
            execution_time) {

            execution_time =
                process->remaining_time;
        }

        scheduler->current_time +=
            execution_time;

        process->remaining_time -=
            execution_time;

        for (int i = 0; i < scheduler->process_count; i++) {

            Process *new_process =
                &scheduler->processes[i];

            if (added[i] == 0 &&
                new_process->arrival_time <=
                    scheduler->current_time) {

                queue_enqueue(queue, new_process);

                added[i] = 1;
            }
        }

        if (process->remaining_time > 0) {

            queue_enqueue(queue, process);

        } else {

            process->completion_time =
                scheduler->current_time;

            calculate_process_metrics(process);

            completed_count++;
        }

        if (adaptive != 0 && completed_count < scheduler->process_count) {
            time_quantum = workload_adaptive_quantum_remaining(
                scheduler->processes,
                scheduler->process_count
            );
        }
    }

    queue_destroy(queue);
}

void scheduler_run_round_robin(
    Scheduler *scheduler,
    int time_quantum
) {
    scheduler_run_round_robin_internal(scheduler, time_quantum, 0);
}

void scheduler_run_adaptive(Scheduler *scheduler) {

    scheduler_run_round_robin_internal(scheduler, 0, 1);
}