#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 100
#define MAX_GANTT 1000

typedef struct {
    int pid;  // Process ID (unique identifier for each process)
    int arrival;
    int burst; // Burst time: total CPU time required by the process
    int remaining; // Remaining burst time: how much CPU time the process still needs
    int priority;
    int completion;
    int turnaround; // Turnaround time = completion time - arrival time
                    // Total time the process spent in the system

    int waiting; // Waiting time = turnaround time - burst time
                // Time the process spent waiting in the ready queue

    int inQueue; // Flag indicating whether the process is currently in the ready queue
                 // Prevents inserting the same process multiple times

    int finished; // Flag indicating the process has completed execution
                  // Used to count finished processes in the simulation
} Process;

void inputProcesses(Process p[], int n);

void priorityRoundRobin(Process processes[], int n, int quantum);

void printResults(Process processes[], int n);


#endif
