#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LIST_NODE{
    void* data;
    struct LIST_NODE* next;
}LIST_NODE;

void ADD_ON_TOP(LIST_NODE*,void* data);

#endif //LINKEDLIST_H
