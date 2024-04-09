#include "TreeSearch.h"

void INORDER(Node *root){
    Node* next=root;
    StackNode* stack;
    while(next!=NULL){
        PUSH(stack,next);
        next=next->left;
    }
}