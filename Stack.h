//one way linked list with addition on top
#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

typedef LIST_NODE STACK_NODE;

void* POP(STACK_NODE** stack);

void* TOP(STACK_NODE* stack);

void PUSH(STACK_NODE** stack,void* data);

bool STACK_EMPTY(STACK_NODE *stack);

STACK_NODE *STACK_INITIALIZE();

#endif //STACK_H
