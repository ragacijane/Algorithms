//one way linked list with addition on top
#ifndef STACK_H
#define STACK_H
typedef struct StackNode{
    void* data;
    struct StackNode* next;
}StackNode;

void* POP(StackNode* stack);
void PUSH(StackNode* stack,void* data);
int STACK_EMPTY(StackNode *stack);
#endif //STACK_H
