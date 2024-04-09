#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

typedef LIST_NODE QUEUE_NODE;


QUEUE_NODE *QUEUE_INITIALIZE();

bool QUEUE_EMPTY(QUEUE_NODE* queue);

void INSERT(QUEUE_NODE** queue,void* data);

void* DELETE(QUEUE_NODE** queue);


#endif //QUEUE_H