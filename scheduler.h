#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 100
#define MAX_GANTT 1000

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
    int inQueue;
    int finished;
} Process;

void inputProcesses(Process p[], int n);
void roundRobin(Process p[], int n, int quantum, int gantt[], int *ganttSize);
void calculateTimes(Process p[], int n);
void printGanttChart(int gantt[], int ganttSize);
void printResults(Process p[], int n);

#endif