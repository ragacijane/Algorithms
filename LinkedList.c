#include "LinkedList.h"

void ADD_ON_TOP(LIST_NODE** root,void* data){
    LIST_NODE *newNode=(LIST_NODE*) malloc(sizeof (LIST_NODE));
    newNode->data=data;
    newNode->next=*root;
    *root=newNode;
}

void ADD_ON_BOTTOM(LIST_NODE** root,void* data){
    LIST_NODE* tmp = *root;
    LIST_NODE* newNode=(LIST_NODE*) malloc(sizeof(LIST_NODE));
    newNode->data=data;
    newNode->next=NULL;
    if(tmp==NULL){
        *root=newNode;
        return;
    }
    if(tmp->next==NULL){
        tmp->next=newNode;
        return;
    }
    tmp=GET_TAIL(*root);
    tmp->next=newNode;
}

void* DELETE_ELEMENT(LIST_NODE** root, LIST_NODE* node){
    LIST_NODE* temp=*root,*prev,*next;
    void *data=NULL;
    if(temp==NULL)return NULL;
    if(temp == node){
        *root=temp->next;
        data=temp->data;
        free(node);
        return data;
    }
    prev=temp;
    temp=temp->next;
    next=temp->next;
    while(temp!=NULL){
        if(temp == node){
            prev->next=next;
            data=temp->data;
            free(node);
            break;
        }
        prev=temp;
        temp=next;
        next=temp->next;
    }
    return data;
}

LIST_NODE* GET_TAIL(LIST_NODE* root){
    LIST_NODE* temp=root;
    if(temp==NULL)return NULL;
    while(true){
        if(temp->next == NULL)break;
        temp=temp->next;
    }
    return temp; // &temp, *temp or temp
}
