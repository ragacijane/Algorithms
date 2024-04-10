#include "Stack.h"
typedef LIST_NODE STACK_NODE;

void* POP(STACK_NODE** stack){
    STACK_NODE *tmp=*stack;
    void* data=tmp->data;
    DELETE_ELEMENT(stack, tmp);
    return data;
}

void* TOP(STACK_NODE* stack){
    return stack->data;
}

void PUSH(STACK_NODE** stack,void* data){
    ADD_ON_TOP(stack,data);
}

bool STACK_EMPTY(STACK_NODE *stack){
    if(stack==NULL)return true;
    else return false;
}

STACK_NODE *STACK_INITIALIZE(){return NULL;}