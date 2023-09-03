#ifndef UTIL_H
#define UTIL_H

#include "list.h"
#include "queue.h"

List* QueueToList(Queue* Q);
Queue* ListToQueue(List* L);

#endif // UTIL_H