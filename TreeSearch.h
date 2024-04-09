#ifndef TREESEARCH_H
#define TREESEARCH_H

#include <stdbool.h>
#include "Stack.h"

typedef struct BinaryNODE{
    void *data;
    bool visited;
    struct BinaryNODE *left,*right;
}BinaryNODE;

typedef void (*UnknownFunction)(void *);

void INORDER_Binary(BinaryNODE*,UnknownFunction);

void LEVELORDER_Binary(BinaryNODE*,UnknownFunction);

void POSTORDER_Binary(BinaryNODE*,UnknownFunction);

void PREORDER_Binary(BinaryNODE*,UnknownFunction);
#endif