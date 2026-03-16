#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE 100

typedef struct {
    int items[MAX_QUEUE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
/* Adds a new element to the queue */
void enqueue(Queue *q, int value);
/* Removes and returns the first element in the queue */
int dequeue(Queue *q);

#endif