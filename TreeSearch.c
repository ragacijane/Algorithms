#include "TreeSearch.h"
//TODO not working!!!!
void INORDER(Node *root){
    Node* next=root;
    StackNode* stack;//initialize!!!
    while(next!=NULL){
        PUSH(stack,next);
        next=next->left;
    }
    if(!STACK_EMPTY(stack)){
        next=POP(stack);
        // Do the function
        next = next->right;
    }
    else return;
}