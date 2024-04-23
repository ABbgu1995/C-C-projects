#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "stdio.h"
#include "Defs.h"
#include<stdbool.h>


typedef struct LinkedList_t *LinkedList; //
typedef struct Node_t *Node; //
// by doing 'struct LinkedList_t linklist' in the main generate an error
//typedef enum {LinkedListSuccess, LinkedListFailed, LinkedListFailRead, LinkedListBadArg} LinkedListResult;

LinkedList createLinkedList(FreeFunction freeFunction, PrintFunction printFunction, CopyFunction copyFunction, EqualFunction equalElements);
status destroyNode(Node node, FreeFunction deepFreeNode);
void destroyList(LinkedList);
status appendNode(LinkedList linkedList, Element element);
status deleteNode(LinkedList linkedList, Element element);
status displayList(LinkedList linkedList);
Element getDataByIndex(LinkedList linkedList, int element_index);
int getLengthList(LinkedList linkedList);
Element searchByKeyInList(LinkedList linkedList, Element element);

#endif



