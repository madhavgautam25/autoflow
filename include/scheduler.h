#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "process.h"

typedef struct {
    Process *processes;
    int process_count;
    int capacity;
    int current_time;
} Scheduler;

Scheduler *scheduler_create(int capacity);

void scheduler_destroy(Scheduler *scheduler);

int scheduler_add_process(
    Scheduler *scheduler,
    int pid,
    int arrival_time,
    int burst_time,
    int priority
);

void scheduler_print_processes(Scheduler *scheduler);

void scheduler_run_fcfs(Scheduler *scheduler);

void scheduler_run_sjf(Scheduler *scheduler);

#endif