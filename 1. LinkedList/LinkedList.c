#include"LinkedList.h"

LinkedList* InitList(void){
    LinkedList *newList = (LinkedList*)malloc(sizeof(LinkedList));
    
    newList->first = (Node*)malloc(sizeof(Node));
    newList->first->next = NULL;
    newList->cur = NULL;
    newList->before = NULL;
    newList->numOfData = 0;
    
    return newList;
}

uint AddData(LinkedList* tgt, ldata data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->data = data;
    newNode->next = tgt->first->next;
    tgt->first->next = newNode;
    tgt->numOfData++;
    
    return tgt->numOfData;
}

uint DeleteCurrentData(LinkedList* tgt){
    tgt->before->next = tgt->cur->next;
    free(tgt->cur);
    tgt->cur = tgt->before;
    tgt->numOfData--;
    
    return tgt->numOfData;
}

ldata LFirst(LinkedList* tgt){
    tgt->cur = tgt->first->next;
    tgt->before = tgt->first;
    
    return tgt->cur->data;
}

ldata LNext(LinkedList* tgt){
    tgt->before = tgt->cur;
    tgt->cur = tgt->cur->next;
    
    return tgt->cur->data;
}
