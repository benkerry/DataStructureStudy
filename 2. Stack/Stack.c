#include "Stack.h"

Stack* InitStack(void){
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    newStack->top = NULL;
    newStack->numOfData = 0;
    
    return newStack;
}

uint SPush(Stack* tgt, sdata data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->before = tgt->top;
    tgt->top = newNode;
    
    tgt->numOfData++;
    
    return tgt->numOfData;
}

sdata SPop(Stack* tgt){
    sdata rtn = tgt->top->data;
    tgt->top = tgt->top->before;
    
    tgt->numOfData--;
    
    return rtn;
}

sdata SPick(Stack* tgt){
    return tgt->top->data;
}
