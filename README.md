# AutoFlow

A workload-aware adaptive CPU scheduling library written in C.

## Overview

AutoFlow is a reusable C library for simulating and evaluating CPU scheduling strategies.

The library analyzes process workload characteristics and dynamically determines scheduling behavior instead of relying on a single fixed scheduling policy.

## Objectives

- Provide a reusable CPU scheduling library in C
- Implement standard scheduling algorithms as baselines
- Analyze workload characteristics
- Develop a custom adaptive scheduling mechanism
- Calculate scheduling performance metrics
- Provide a clean and simple API
- Package the project as a reusable static library

## Planned Features

- Process management
- Ready queue management
- FCFS scheduling
- SJF scheduling
- Priority scheduling
- Round Robin scheduling
- Workload analysis
- Adaptive scheduling
- Scheduling metrics
- Gantt chart generation
- Static library support

## Project Structure

```text
AutoFlow/
├── include/       # Public header files
├── src/           # Library implementation
├── examples/      # Example programs
├── tests/         # Test cases
├── Makefile       # Build automation
├── README.md      # Project documentation
├── LICENSE        # Project license
└── .gitignore     # Ignored files