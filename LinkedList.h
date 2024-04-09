#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LIST_NODE{
    void* data;
    struct LIST_NODE* next;
}LIST_NODE;

void ADD_ON_TOP(LIST_NODE** root,void* data);

void ADD_ON_BOTTOM(LIST_NODE** root,void* data);

void DELETE_NODE(LIST_NODE** root,LIST_NODE* node);

LIST_NODE* GET_TAIL(LIST_NODE*);
#endif //LINKEDLIST_H
