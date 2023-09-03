#include "util.h"

#include <stdlib.h>

// Convierte una cola a una lista
List* QueueToList(Queue* Q)
{
    List* result = createList();

    while (Q->front != NULL)
    {
        pushBack(result, top(Q));
        pop(Q);
    }
    
    return result;
}

// Convierte una lista a una cola
Queue* ListToQueue(List* L)
{
    Queue* result = createQueue();

    firstList(L);
    while (L->current != NULL)
    {
        push(result, popBack(L));
    }
    
    return result;
}
