#include "TreeSearch.h"

void INORDER_Binary(BINARY_NODE *root, UnknownFunction function){
    BINARY_NODE* next=root;
    STACK_NODE* stack=STACK_INITIALIZE();
    PUSH(&stack,next);
    next=next->left;
    while(!STACK_EMPTY(stack)){
        while(next!=NULL){
        PUSH(&stack,next);
        next=next->left;
        }
        if(!STACK_EMPTY(stack)){
            next=POP(&stack);
            function(next->data);
            next = next->right;
        }
        else return;
    }
}

void POSTORDER_Binary(BINARY_NODE *root, UnknownFunction function){
    BINARY_NODE *next=root;
    STACK_NODE * stack=STACK_INITIALIZE();
    while(next!=NULL){
        next->visited=false;
        PUSH(&stack,next);
        next=next->left;
    }
    while(!STACK_EMPTY(stack)){
        next= POP(&stack);
        if(!next->visited){
            next->visited=true;
            PUSH(&stack,next);
            next=next->right;
            while(next!=NULL){
                PUSH(&stack,next);
                next=next->left;
            }
        }
        else{
            next->visited=false;
            function(next);
        }
    }
}

void PREORDER_Binary(BINARY_NODE *root, UnknownFunction function){
    BINARY_NODE *next;
    STACK_NODE *stack=STACK_INITIALIZE();
    PUSH(&stack,root);
    while(!STACK_EMPTY(stack)){
        next= POP(&stack);
        while(next!=NULL){
            function(next);
            if(next->right!=NULL)
                PUSH(&stack,next->right);
            next=next->left;
        }
    }
}

void LEVELORDER_Binary(BINARY_NODE *root, UnknownFunction function){
    BINARY_NODE *next=root;
    QUEUE_NODE *queue=QUEUE_INITIALIZE();
    INSERT(queue,next);
    while (!QUEUE_EMPTY(queue)){
        next = DELETE(queue);
        function(next);
        if(next->left != NULL)
            INSERT(queue,next->left);
        if(next->right != NULL)
            INSERT(queue,next->right);
    }
}