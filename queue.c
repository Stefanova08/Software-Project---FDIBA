#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->rear < q->front;
}

int isFull(Queue *q) {
    return q->rear == MAX_QUEUE - 1;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue overflow!\n");
        exit(1);
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue underflow!\n");
        exit(1);
    }
    return q->items[q->front++];
}