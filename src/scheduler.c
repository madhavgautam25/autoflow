#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include "metrics.h"

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