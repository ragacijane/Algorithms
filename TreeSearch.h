#ifndef TREESEARCH_H
#define TREESEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

typedef struct Node{
    void *data;
    struct Node *left,*right;
}Node;

#endif