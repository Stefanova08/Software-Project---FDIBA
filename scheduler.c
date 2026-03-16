#include <stdio.h>
#include "scheduler.h"
#include "queue.h"

void inputProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Enter Process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Priority (smaller number = higher priority): ");
        scanf("%d", &p[i].priority);

        p[i].remaining = p[i].burst;
        p[i].completion = 0;
        p[i].turnaround = 0;
        p[i].waiting = 0;
        p[i].inQueue = 0;
        p[i].finished = 0;
    }
}

int findHighestPriority(Process p[], int n, int time) {
    int highestPriority = -1;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= time && p[i].remaining > 0) {
            if (highestPriority == -1 || p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
            }
        }
    }

    return highestPriority;
}

void roundRobin(Process p[], int n, int quantum, int gantt[], int *ganttSize) {
    Queue q;
    initQueue(&q);

    int time = 0;
    int completed = 0;
    *ganttSize = 0;

    while (completed < n) {
        int highestPriority = findHighestPriority(p, n, time);

        if (highestPriority == -1) {
            time++;
            continue;
        }
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time &&
                p[i].remaining > 0 &&
                p[i].inQueue == 0 &&
                p[i].priority == highestPriority) {

                enqueue(&q, i);
                p[i].inQueue = 1;
            }
        }

        if (isEmpty(&q)) {
            time++;
            continue;
        }

        int idx = dequeue(&q);
        p[idx].inQueue = 0;

        gantt[*ganttSize] = p[idx].pid;
        (*ganttSize)++;

        if (p[idx].remaining > quantum) {

            p[idx].remaining -= quantum;
            time += quantum;

        }
        else {
            time += p[idx].remaining;
            p[idx].remaining = 0;
            p[idx].completion = time;
            p[idx].finished = 1;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time &&
                p[i].remaining > 0
                && p[i].inQueue == 0 &&
                i != idx &&
                p[i].priority == highestPriority) {

                enqueue(&q, i);
                p[i].inQueue = 1;
            }
        }

        if (p[idx].remaining > 0 &&
            p[idx].priority == highestPriority) {

            enqueue(&q, idx);
            p[idx].inQueue = 1;
        }
    }
}

void calculateTimes(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void printGanttChart(int gantt[], int ganttSize) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttSize; i++) {
        printf("P%d", gantt[i]);
        if (i != ganttSize - 1) {
            printf(" | ");
        }
    }
    printf("\n");
}

void printResults(Process p[], int n) {
    float totalWT = 0, totalTAT = 0;

    printf("\n%-8s %-8s %-8s %-10s %-8s %-8s %-8s\n",
           "PID", "AT", "BT", "Priority", "CT", "TAT", "WT");

    for (int i = 0; i < n; i++) {
        printf("%-8d %-8d %-8d %-10d %-8d %-8d %-8d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}