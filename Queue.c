#include "Queue.h"

QUEUE_NODE *QUEUE_INITIALIZE(){return NULL;}

bool QUEUE_EMPTY(QUEUE_NODE* queue){
    if(queue==NULL)return true;
    else return false;
}

void INSERT(QUEUE_NODE** queue,void* data){
    ADD_ON_BOTTOM(queue,data);
}

void* DELETE(QUEUE_NODE** queue){
    QUEUE_NODE* node= GET_TAIL(*queue);
    void* data=node->data;
    DELETE_ELEMENT(queue, node);
    return data;
}

