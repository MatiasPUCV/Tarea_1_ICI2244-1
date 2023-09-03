#include "util.h"

#include <stdlib.h>

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
