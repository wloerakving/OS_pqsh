# PQSH: Process Queue Scheduler 
## Overview 
This project is developed as part of our Operating Systems course to simulate and test different process scheduling algorithms.
## Features 
Multiple Scheduling Policies: FIFO, Round Robin, and Shortest Job First (SJF). <br>
Signal Handling: Custom signal registration and handling. <br>
Timestamp Recording: Precise process timing and logging. <br>
Debugging Utilities: Macros for logging and debugging. 

## Getting Started 
### Prerequisites:
* GCC (GNU Compiler Collection) <br>
* Make : Building the Project
### Building the project:
1. clone the repository:
 ```bash
git clone https://github.com/yourusername/pqsh.git 
cd pqsh
```
2. compile the project:
```bash
make
```
### Running the Scheduler 
To run the scheduler:<br>
```bash
./bin/pqsh 
```
### Testing the Scheduler
To run the test suite: 
```bash
make test
```
This command will compile and execute the tests located in the tests/ directory. 

## Directory Structure 
include/pq/: Header files defining the interface and structures for different components. <br>
src/: Source files implementing the core functionality of PQSH. <br>
tests/: Unit tests and scripts to validate the scheduler's functionality. <br>
bin/: Compiled binaries of the scheduler and test programs. 

## Components 
### Scheduler 
The scheduler component manages process queues and implements different scheduling policies: 
 
##### FIFO (First In, First Out): Processes are scheduled in the order they arrive. 
##### Round Robin: Processes are assigned a fixed time slice and scheduled in a cyclic order. 
##### SJF (Shortest Job First): Processes with the shortest execution time are scheduled first. 
The scheduler's structure includes queues for running, waiting, and finished processes. It tracks total turnaround and response times to evaluate scheduling performance. 
 
### Signal Handling 
Signal handling in PQSH allows for the registration of custom signal handlers. This feature is critical for managing asynchronous events, such as process timeouts and interrupts. The signal handlers ensure that processes are properly started, paused, and resumed based on system signals. 
 
### Timestamp Recording 
Timestamp utilities provide precise measurements of process start, stop, and duration times. This feature is essential for performance analysis and debugging, allowing for accurate tracking of process execution timelines. 
 

## Code Implementation 
#### timestamp: Declares the function for recording timestamps. 
#### signal: Defines signal handling functions and handlers. 
#### scheduler: Declares the scheduler structure, policies, and related functions. 
#### queue: Defines the queue structure and functions for queue operations. 
#### process: Declares the process structure and functions for process management. 
#### options: Declares functions for parsing command-line options. 
#### macros: Defines macros for logging and utility functions. 

## Testing 
The tests/ directory contains unit tests and scripts to validate the functionality of the scheduler. <br>
The tests ensure that each component works correctly and that the scheduling policies produce the expected results. 
