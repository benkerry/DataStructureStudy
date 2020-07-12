#include"Stack.h"

int FindChar(char* src, char tgt){
    int i = 0;
    
    while(src[i] != '\0'){
        if(src[i] == tgt)
            return 1;
        i++;
    }
    
    return 0;
}

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
    
    free(tgt->top);
    tgt->top = tgt->top->before;
    
    tgt->numOfData--;
    
    return rtn;
}

sdata SPick(Stack* tgt){
    return tgt->top->data;
}

Stack* CopyStack(Stack* src){
    Stack *result = InitStack();
    sdata temp[src->numOfData];
    
    for(int i = src->numOfData - 1; i >= 0; i--){
        temp[i] = SPop(src);
    }
    for(int i = 0; i < src->numOfData; i++){
        SPush(result, temp[i]);
    }
    
    return result;
}
