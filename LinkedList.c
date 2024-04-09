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

void DELETE_NODE(LIST_NODE** root,LIST_NODE* delNode){
    LIST_NODE* temp=*root,*prev,*next;
    if(temp==delNode){
        *root=temp->next;
        //free(delNode->data);
        free(delNode);
        return;
    }
    prev=temp;
    temp=temp->next;
    next=temp->next;
    while(temp!=NULL){
        if(temp==delNode){
            prev->next=next;
            //free(delNode->data);
            free(delNode);
            return;
        }
        prev=temp;
        temp=next;
        next=temp->next;
    }
}

LIST_NODE* GET_TAIL(LIST_NODE* root){
    LIST_NODE* temp=root;
    if(temp==NULL)return NULL;
    while(true){
        if(temp->next == NULL)break;
        temp=temp->next;
    }
    return temp; //TODO &temp, *temp or temp
}
