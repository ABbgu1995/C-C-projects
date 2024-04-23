//no ine except us is doing include for this c file
#include "LinkedList.h"
#include <string.h>
#include <stdio.h>
#include "malloc.h"
#include "Jerry.h"

struct Node_t {
    // in order to define a linkedlist, we first need to set a node struct
    Element e; //data of the node, a pointer to element
    Node next;
};


struct LinkedList_t {
    int elements_amount; //how many elements exists in the linked list
    Node head; // pointer to Node_t
    Node end;
    CopyFunction copyElement;
    FreeFunction freeElement;
    PrintFunction printElement;
    EqualFunction equalElements;
};

LinkedList createLinkedList(FreeFunction freeFunction, PrintFunction printFunction, CopyFunction copyFunction, EqualFunction equalElements){

    if(freeFunction==NULL || printFunction==NULL) return NULL;

    LinkedList linkedList = (LinkedList) malloc(sizeof (struct LinkedList_t));
    if (linkedList == NULL) return NULL;

    linkedList->head=NULL;
    linkedList->end=NULL;
    linkedList->copyElement=copyFunction;
    linkedList->freeElement=freeFunction;
    linkedList->printElement=printFunction;
    linkedList->equalElements=equalElements;
    linkedList->end=linkedList->head;
    linkedList->elements_amount=0;
    return linkedList;
}

status appendNode(LinkedList linkedList, Element element){

    if(linkedList==NULL) return failure;

    Node newNode=(Node) malloc(sizeof (struct Node_t));
    if(newNode==NULL) return failure;

    // use the user copy function in order to fill the node data
    newNode->e=linkedList->copyElement(element);


    if(newNode->e==NULL) {
        destroyNode(newNode, linkedList->freeElement);
        newNode=NULL;
        return failure;
    }
    if(newNode->e==NULL){
        free(newNode);
        newNode=NULL;
        return failure;
    }

    newNode->next=NULL;
    if(linkedList->elements_amount==0) // first append
    {
        linkedList->head=newNode;
        linkedList->end=linkedList->head;
    }
    else { // the list already contains nodes
        linkedList->end->next = newNode;
        linkedList->end = newNode;
    }
    linkedList->elements_amount++;
    return success;

}

status deleteNode(LinkedList linkedList, Element element){

    if(linkedList==NULL) return failure;

    Node runner = linkedList->head;

    // check if there are no nodes to delete
    if(linkedList->elements_amount==0){
        free(runner);
        runner=NULL;
        return failure;
    }

    if(linkedList->elements_amount>1) {
        while (runner->next != NULL) {
            // in case of the first node is match one
            if (linkedList->equalElements(linkedList->head->e, element)) {
                Node current_node = linkedList->head;
                linkedList->head = linkedList->head->next;
                linkedList->freeElement(current_node->e);
                free(current_node);
                current_node=NULL;
                linkedList->elements_amount--;
                return success;
            }
            // in case of the last node is the match one
            if (runner->next == linkedList->end && linkedList->equalElements(linkedList->end->e, element)) {
                Node current_node = linkedList->end;
                linkedList->end = runner;
                linkedList->end->next = NULL;
                linkedList->freeElement(current_node->e);
                free(current_node);
                current_node=NULL;
                linkedList->elements_amount--;
                return success;
            }

            if (linkedList->equalElements(runner->next->e, element)) {
                Node current_node = runner->next;
                runner->next = runner->next->next;
                linkedList->freeElement(current_node->e);
                free(current_node); // free the node allocation from appendNode function
                current_node=NULL;
                linkedList->elements_amount--;
                return success;
            }
            // keep reading the nodes
            runner = runner->next;
        }
    }
    else {
        // if the linked list contains only one node
        if (linkedList->equalElements(linkedList->head->e,element)) {
            linkedList->freeElement(linkedList->head->e);
            free(linkedList->head);
            linkedList->head=NULL;
            linkedList->end=NULL;
            linkedList->elements_amount--;
            return success;
        }
    }
    return failure;


}
void destroyList(LinkedList linkedList){
    // the function doing deep destroy to a linked list
    if(linkedList==NULL) return;
    Node current=linkedList->head;
    Node temp;
    if (linkedList->elements_amount>=1) {
        while (current != NULL) {
            temp = current->next;
            linkedList->freeElement(current->e);
            free(current);
            current= NULL;
            current = temp;
        }
    }
        free(current);
        current=NULL;
        free(linkedList);
        linkedList = NULL;
};

status displayList(LinkedList linkedList){
    if(linkedList==NULL) return failure;
    Node current=linkedList->head;
    while(current!=NULL){
        linkedList->printElement(current->e);
        current=current->next;
    }
    return success;
}

Element getDataByIndex(LinkedList linkedList, int element_index){
    if(linkedList==NULL) return NULL;
    if(element_index>linkedList->elements_amount || element_index<=0) return NULL;
    Node current=linkedList->head;
    for (int i=1; i<element_index; i++)
        current=current->next;
    return current->e;
};

int getLengthList(LinkedList linkedList){
    if(linkedList==NULL) return -1; // in case of empty argument
    return linkedList->elements_amount;
}

Element searchByKeyInList(LinkedList linkedList, Element element){
    // the function is using the compare function of the user to find the key or part of key
    if(linkedList == NULL || element == NULL) return NULL;
    Node current=linkedList->head;
    while(current!=NULL) {
        if (linkedList->equalElements(current->e, element))
            return current->e;
        current=current->next;
    }
    return NULL;
}

status destroyNode(Node node, FreeFunction deepFreeNode){
    if (node == NULL || deepFreeNode ==NULL)
        return failure;
    deepFreeNode(node->e);
        free(node);
        return success;
}
