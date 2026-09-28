#include <stdio.h>
#include "workload.h"


int main() {

    Process processes[4];

    processes[0].burst_time = 8;
    processes[1].burst_time = 3;
    processes[2].burst_time = 12;
    processes[3].burst_time = 2;

    double average =
        workload_average_burst(
            processes,
            4
        );

    int quantum =
        workload_adaptive_quantum(
            processes,
            4
        );

    printf("Average Burst Time: %.2f\n", average);
    printf("Adaptive Time Quantum: %d\n", quantum);

    return 0;
}