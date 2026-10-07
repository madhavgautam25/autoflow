# AutoFlow

A workload-aware adaptive CPU scheduling library written in C.

## Overview

AutoFlow is a lightweight C library for simulating and experimenting with CPU scheduling algorithms.

It provides commonly used scheduling algorithms along with a workload-aware mechanism that automatically determines a suitable Round Robin time quantum based on the workload.

AutoFlow is designed for learning, experimentation, algorithm comparison, and understanding the internal implementation of CPU scheduling.

> AutoFlow is a CPU scheduling simulation library. It is not a real operating-system kernel scheduler.

---

## Features

- Process management
- Ready queue implementation using a circular queue
- FCFS scheduling
- Shortest Job First scheduling
- Priority scheduling
- Priority aging for starvation protection
- Round Robin scheduling
- Workload analysis
- Adaptive Round Robin time quantum
- Waiting time calculation
- Turnaround time calculation
- Response time calculation
- Reusable static library
- Simple public API

---

## Scheduling Algorithms

### FCFS

First Come First Serve executes processes according to their arrival/order in the scheduler.

### SJF

Shortest Job First selects the available process with the smallest burst time.

AutoFlow currently implements non-preemptive SJF.

### Priority Scheduling

Priority scheduling selects the available process with the highest priority.

In AutoFlow, a lower numerical priority value represents a higher priority.
To reduce starvation, a waiting process improves its effective priority by 1
for every 10 units of waiting time. The original priority value is unchanged;
only the effective priority is used to choose the next process.

### Round Robin

Round Robin gives each process a fixed time quantum and places unfinished processes back into the ready queue.

AutoFlow uses a circular queue for efficient ready-queue management.

### Adaptive Scheduling

AutoFlow can automatically calculate a time quantum based on the workload.

The initial rule is:

Adaptive Quantum = Average Burst Time / 2

The calculated quantum is constrained to a minimum of 1 and a maximum of 10.
During adaptive Round Robin, AutoFlow recalculates the quantum after each
process turn using the average remaining burst time of unfinished processes.

This provides a simple and explainable workload-aware scheduling mechanism.

---

## Architecture

```text
                    AutoFlow
                       |
              +--------+--------+
              |                 |
          Process Model      Scheduler
                                |
              +-----------------+----------------+
              |          |          |             |
             FCFS       SJF      Priority     Round Robin
                                                   |
                                             Circular Queue
                                                   |
                                           Workload Analysis
                                                   |
                                           Adaptive Quantum
                                                   |
                                         Scheduling Metrics