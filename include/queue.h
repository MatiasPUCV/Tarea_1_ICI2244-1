#ifndef QUEUE_H
#define QUEUE_H

typedef struct queueNode
{
    void* data;
    struct queueNode* next;
} queueNode;

typedef struct
{
    queueNode* front;
    queueNode* back;
} Queue;

Queue* createQueue();
void push(Queue* queue, void* data);
void pop(Queue* queue);
void* top(Queue* queue);

#endif // QUEUE_H
