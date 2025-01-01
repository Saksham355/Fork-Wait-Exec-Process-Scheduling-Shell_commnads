# C Programming Assignment

## Question 1

### Description

Write a program where the parent process creates 7 child processes. Each child generates 4 random numbers from 1 to 100, calculates their mean, prints it, and returns. The parent should wait for all children to finish before returning.

### Files

- `q1.c`: Contains the main function and the implementation.

### Instructions

1. The parent process should fork 7 times.
2. Each child should generate 4 random numbers, calculate their mean, and print it.
3. The parent process should call `wait()` 7 times to wait for each child.
4. The printed output should contain 7 means, one from each child.

## Question 2

### Description

Perform a binary search on a 16-element sorted array by dividing the array between parent and child processes. Each child process operates on half of its parent's array. The child process that finds the target value should print its index. If the target is not in the array, print -1.

### Files

- `q2.c`: Contains the main function and the implementation.

### Instructions

1. Define a sorted 16-element array.
2. Ask the user for a target value.
3. Use fork() to create child processes, each operating on half of the parent's array.
4. Each parent should wait for their child to finish.
5. Print the index of the target value, or -1 if not found.

## Question 3

### Description

Create implementations of basic UNIX commands (`date`, `cal`, `uptime`) and a main program to run these commands as child processes.

### Folder Structure

- `q3`
  - `date.c`: Implementation of the `date` command.
  - `cal.c`: Implementation of the `cal` command.
  - `uptime.c`: Implementation of the `uptime` command.
  - `main.c`: Program to run the above commands as child processes.
  - `Makefile`: To build the executables.

### Instructions

1. Implement the `date`, `cal`, and `uptime` commands.
2. Create 3 child processes using `fork()`, each running one of the commands.
3. The parent process should wait for all children to finish.
4. Use the `Makefile` to compile the programs.

## Question 4

### Description

Simulate different CPU scheduling algorithms: FIFO, SJF, SRTF, and RR.

### Files

- `q4.c`: Contains the main function and the implementation.

### Instructions

1. Accept input for `n` processes, where each process has a unique ID, arrival time, burst time, and (for RR) time quantum.
2. Implement FIFO, SJF, SRTF, and RR algorithms.
3. Calculate and display the order of execution, average response time, and average turnaround time for each algorithm.
4. Use `fork()`, `wait()`, `sleep()`, and `kill()` functions as needed.
