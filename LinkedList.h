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

//RETURNS data that is deleted or NULL if list doesnt contain data
void* DELETE_ELEMENT(LIST_NODE** root, LIST_NODE* node);

LIST_NODE* GET_TAIL(LIST_NODE*);
#endif //LINKEDLIST_H
