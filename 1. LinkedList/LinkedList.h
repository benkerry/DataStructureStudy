#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdlib.h>

typedef int ldata;
typedef unsigned int uint;

typedef struct _node{
    ldata data;
    struct _node* next;
} Node;

typedef struct{
    Node* first;
    Node* cur;
    Node* before;
    uint numOfData;
} LinkedList;

LinkedList* InitList(void);
uint AddData(LinkedList*, ldata);
uint DeleteCurrentData(LinkedList*);
ldata LFirst(LinkedList*);
ldata LNext(LinkedList*);

#endif
