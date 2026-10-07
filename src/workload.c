#include <stdlib.h>
#include "workload.h"

double workload_average_burst(
    Process *processes,
    int process_count
) {

    if (processes == NULL || process_count <= 0) {
        return 0.0;
    }

    int total_burst = 0;

    for (int i = 0; i < process_count; i++) {
        total_burst += processes[i].burst_time;
    }

    return (double) total_burst / process_count;

}

int workload_adaptive_quantum(
    Process *processes,
    int process_count
) {

    double average = workload_average_burst(processes, process_count);

    if (average <= 0) {
        return 1;
    }

    int quantum = (int) (average / 2);

    if (quantum < 1) {
        quantum = 1;
    }

    if (quantum > 10) {
        quantum = 10;
    }

    return quantum;
}

int workload_adaptive_quantum_remaining(
    Process *processes,
    int process_count
) {

    if (processes == NULL || process_count <= 0) {
        return 1;
    }

    int total_remaining = 0;
    int unfinished_count = 0;

    for (int i = 0; i < process_count; i++) {
        if (processes[i].remaining_time > 0) {
            total_remaining += processes[i].remaining_time;
            unfinished_count++;
        }
    }

    if (unfinished_count == 0) {
        return 1;
    }

    double average =
        (double) total_remaining / unfinished_count;

    int quantum = (int) (average / 2);

    if (quantum < 1) {
        quantum = 1;
    }

    if (quantum > 10) {
        quantum = 10;
    }

    return quantum;
}