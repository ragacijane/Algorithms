//one way linked list with addition on top
#ifndef STACK_H
#define STACK_H
typedef struct StackNode{
    void* data;
    StackNode* next;
};

void PUSH(StackNode* stack,void* data);
#endif //STACK_H
