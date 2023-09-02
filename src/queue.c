#include "queue.h"

#include <stdlib.h>

Queue* createQueue()
{
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->front = NULL;
    newQueue->back = NULL;
    return newQueue;
}

void push(Queue* queue, void* data)
{
    queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
    newNode->data = data;
    newNode->next = NULL;
    
    if (queue->back == NULL)
    {
        queue->front = newNode;
        queue->back = newNode;
    } else
    {
        queue->back->next = newNode;
        queue->back = newNode;
    }
}

void pop(Queue* queue)
{
    if (queue->front == NULL)
        return;
    
    queueNode* temp = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->back = NULL;
    }
    
    free(temp);
}

void* top(Queue* queue)
{
    if (queue->front == NULL) {
        return NULL;
    }
    return queue->front->data;
}