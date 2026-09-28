#ifndef WORKLOAD_H
#define WORKLOAD_H
#include "process.h"

double workload_average_burst(
    Process *processes,
    int process_count
);

int workload_adaptive_quantum(
    Process *processes,
    int process_count
);

#endif