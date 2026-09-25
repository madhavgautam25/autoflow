#include <stdlib.h>
#include "metrics.h"

void calculate_process_metrics(Process *process) {

    if (process == NULL) {
        return;
    }

    process->turnaround_time = process->completion_time - process->arrival_time;

    process->waiting_time = process->turnaround_time - process->burst_time;

    process->response_time = process->start_time - process->arrival_time;


}