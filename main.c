#include <stdio.h>
#include "scheduler.h"

int main() {
    Process processes[MAX_PROCESSES];
    int n, quantum;
    int gantt[MAX_GANTT];
    int ganttSize;

    printf("=== Round-Robin Scheduler Simulation ===\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes!\n");
        return 1;
    }

    inputProcesses(processes, n);

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    if (quantum <= 0) {
        printf("Time quantum must be greater than 0!\n");
        return 1;
    }

    roundRobin(processes, n, quantum, gantt, &ganttSize);
    calculateTimes(processes, n);

    printGanttChart(gantt, ganttSize);
    printResults(processes, n);

    return 0;
}