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