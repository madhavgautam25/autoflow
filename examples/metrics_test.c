#include <stdio.h>

#include "metrics.h"

int main() {

    Process process = {
        1,
        2,
        4,
        4,
        1,
        5,
        12,
        0,
        0,
        0
    };

    calculate_process_metrics(&process);

    printf("Turnaround Time: %d\n", process.turnaround_time);
    printf("Waiting Time: %d\n", process.waiting_time);
    printf("Response Time: %d\n", process.response_time);

    return 0;
}