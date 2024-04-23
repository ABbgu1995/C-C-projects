#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

Element CopyList(Element linklist){
    // flat copy
    if(linklist==NULL) return NULL;
    LinkedList l1 = (LinkedList)linklist;
    return l1;

}

status FreeList(Element elem){
    // deep free list
    if(elem==NULL) return failure;
    destroyList((LinkedList)elem);
    return success;
}

status PrintList(Element elem){
    if(elem==NULL) return failure;
    displayList((LinkedList)elem);
    return success;
}

enum e_bool CompareList(Element list1, Element list2) {
    if(list1==NULL || list2==NULL) return false;
    if(list1==list2)
        return true;
    return false;
}

struct multiValueHashTable_s{
    hashTable hashtable;
    int total_nodes;
    int table_size;
    int hash_number;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    EqualFunction equalValue;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction transformIntoNumber;
};

multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                              CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                                              EqualFunction equalKey, EqualFunction equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber){

    // return NULL is case of hashNumber is zero because it means the table size will be 0
    if(hashNumber<=0) return NULL;

    multiValueHashTable multiValueHashTable1 = (multiValueHashTable) malloc(sizeof (struct multiValueHashTable_s));
    if(multiValueHashTable1==NULL) return NULL;

    multiValueHashTable1->copyKey=copyKey;
    multiValueHashTable1->freeKey=freeKey;
    multiValueHashTable1->printKey=printKey;
    multiValueHashTable1->copyValue=copyValue;
    multiValueHashTable1->freeValue=freeValue;
    multiValueHashTable1->printValue=printValue;
    multiValueHashTable1->equalKey=equalKey;
    multiValueHashTable1->equalValue=equalValue;
    multiValueHashTable1->transformIntoNumber=transformIntoNumber;
    multiValueHashTable1->total_nodes=0;
    multiValueHashTable1->hash_number=hashNumber;
    multiValueHashTable1->hashtable= createHashTable(multiValueHashTable1->copyKey, multiValueHashTable1->freeKey,multiValueHashTable1->printKey,
                                                     CopyList,FreeList, PrintList,multiValueHashTable1->equalKey, multiValueHashTable1->transformIntoNumber, multiValueHashTable1->hash_number);

    return multiValueHashTable1;

}

status addToMultiValueHashTable(multiValueHashTable multiValueHashTable1, Element key,Element value){
    if(multiValueHashTable1==NULL || key == NULL || value == NULL) return failure;

    if(lookupInHashTable(multiValueHashTable1->hashtable,key)==NULL){
        // it means that the key isn't exist so we need to init linkedlist in the value
        LinkedList first_list = createLinkedList(multiValueHashTable1->freeValue, multiValueHashTable1->printValue,
                                                 multiValueHashTable1->copyValue,multiValueHashTable1->equalValue);
        if (first_list==NULL) return failure;
        if(appendNode(first_list, value) == failure)
        {
            destroyList(first_list);
            return failure;
        }
        if(addToHashTable(multiValueHashTable1->hashtable, key, first_list)==success)  // add
            multiValueHashTable1->total_nodes++;
        return success;
    }
    else{
        appendNode((LinkedList)lookupInHashTable(multiValueHashTable1->hashtable,key),value);
        return success;
    }
};

void destroyMultiValueHashTable(multiValueHashTable multiValueHashTable1){
    // the function receive MultiValueHashTable and doing deep free
    if(multiValueHashTable1==NULL) return;
    destroyHashTable(multiValueHashTable1->hashtable);
    free(multiValueHashTable1);
    multiValueHashTable1=NULL;

};

LinkedList lookupInMultiValueHashTable(multiValueHashTable multiValueHashTable1, Element key){
    // the function check if a key exist in the MultiValueHashTable
    if(multiValueHashTable1==NULL || key == NULL) return NULL;
    LinkedList list_exist_check = lookupInHashTable(multiValueHashTable1->hashtable, key);

    //if the list (as key) not exist, destroy the temp list
    if(list_exist_check==NULL)
        return NULL;
    return list_exist_check;
};

status displayMultiValueHashElementsByKey(multiValueHashTable multiValueHashTable1, Element key){
    // the function display the values mapped to the key as argument
    if(multiValueHashTable1==NULL || key == NULL) return failure;
    LinkedList values_list_mapped_to_key = lookupInHashTable(multiValueHashTable1->hashtable, key);
    if(values_list_mapped_to_key!=NULL) {
        displayList(values_list_mapped_to_key);
        return success;
    }
    return failure;
};

status removeFromMultiValueHashTable(multiValueHashTable multiValueHashTable1, Element key, Element value){
    // the function delete a value from a values list mapped to a key
    if(multiValueHashTable1==NULL || key==NULL || value==NULL) return failure;
    LinkedList list_of_values = lookupInHashTable(multiValueHashTable1->hashtable, key);
    if(list_of_values==NULL)
        // the value not exists
        return failure;
    if(deleteNode(list_of_values, value) == success) {
        if (getLengthList(list_of_values) == 0) {
            if (removeFromHashTable(multiValueHashTable1->hashtable, key) == success)
                return success;
            return failure;
        }
        return success;
    }
    return failure;
}
