#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;

    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
} Process;

#endif