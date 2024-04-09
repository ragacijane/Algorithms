#ifndef TREESEARCH_H
#define TREESEARCH_H

#include "Stack.h"
#include "Queue.h"

typedef struct BINARY_NODE{
    void *data;
    bool visited;
    struct BINARY_NODE *left,*right;
}BINARY_NODE;

typedef void (*UnknownFunction)(void *);

void INORDER_Binary(BINARY_NODE*, UnknownFunction);

void LEVELORDER_Binary(BINARY_NODE*, UnknownFunction);

void POSTORDER_Binary(BINARY_NODE*, UnknownFunction);

void PREORDER_Binary(BINARY_NODE*, UnknownFunction);
#endif