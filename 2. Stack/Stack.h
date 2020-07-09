#ifndef __STACK_H__
#define __STACK_H__

#include<stdlib.h>

typedef char sdata;
typedef unsigned int uint;

typedef struct _node{
    sdata data;
    struct _node* before;
} Node;

typedef struct{
    Node* top;
    uint numOfData;
} Stack;

Stack* InitStack(void);
uint SPush(Stack*, sdata);
sdata SPop(Stack*);
sdata SPick(Stack*);

#endif
