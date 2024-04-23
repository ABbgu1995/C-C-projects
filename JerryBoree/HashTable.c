#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h" //not sure if should here
#include <string.h>
#include <stdio.h>
#include "malloc.h"




struct hashTable_s{

    LinkedList* hashtable_array;
    int total_elements;
    int table_size;
    int hash_number;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction transformIntoNumber;
};

// 4 functions so support the linkedlist for each cell in the hashtable and each linkedlist contains keyValuePair node data
Element CopyKeyPair(Element elem){
    if(elem==NULL) return NULL;
    KeyValuePair copy = copyKeyValuePair((KeyValuePair)elem);
    if(copy==NULL) return NULL;
    return copy;
}

status FreeKeyPair(Element elem){
    if(elem==NULL) return failure;
    destroyKeyValuePair((KeyValuePair)elem);
    elem=NULL;
    return success;
}

status PrintKeyPair(Element elem){
    if(elem==NULL) return failure;
    displayKey((KeyValuePair)elem);
    displayValue((KeyValuePair)elem);
    return success;
}

enum e_bool CompareKeyPair(Element elem1, Element elem2){
    if(elem1==NULL || elem2==NULL) return false;
    if(isEqualKey((KeyValuePair)elem1, elem2))
        return true;
    return false;

}

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue,
                          PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){

    if(hashNumber<=0) return NULL;
    hashTable hash_table = (hashTable) malloc(sizeof (struct hashTable_s));
    if(hash_table==NULL) return NULL;

    hash_table->table_size=hashNumber;
    hash_table->hashtable_array = (LinkedList*) malloc(sizeof (LinkedList) * hash_table->table_size);
    if(hash_table->hashtable_array == NULL) return NULL;
    for (int i=0; i<hash_table->table_size; i++)
        hash_table->hashtable_array[i]=NULL;
    hash_table->copyKey=copyKey;
    hash_table->freeKey=freeKey;
    hash_table->printKey=printKey;
    hash_table->copyValue=copyValue;
    hash_table->freeValue=freeValue;
    hash_table->printValue=printValue;
    hash_table->equalKey=equalKey;
    hash_table->transformIntoNumber=transformIntoNumber;
    hash_table->total_elements=0;
    hash_table->hash_number=hashNumber;
    return hash_table;
}

status destroyHashTable(hashTable hashTable1){
    if(hashTable1==NULL) return failure;

    for (int i=0; i<hashTable1->hash_number; i++){
        // destroy and delete each linked list within the hashTable
        destroyList(hashTable1->hashtable_array[i]);
        hashTable1->hashtable_array[i]=NULL;
    }
    free(hashTable1->hashtable_array);
    hashTable1->hashtable_array=NULL;
    free (hashTable1);
    hashTable1=NULL;
    return success;
}
status addToHashTable(hashTable hashTable1, Element key,Element value){
    if (hashTable1==NULL || key == NULL || value == NULL) return failure;
    KeyValuePair temp_keyValuePair = createKeyValuePair(key, value, hashTable1->copyKey, hashTable1->freeKey, hashTable1->equalKey, hashTable1->printKey, hashTable1->copyValue,
                                           hashTable1->freeValue, hashTable1->printValue);

    if (temp_keyValuePair == NULL) return failure;

    // use the hash function to find the right location to insert the value
    int location_in_hashtable = hashTable1->transformIntoNumber(getKey(temp_keyValuePair))%(hashTable1->hash_number);

    if(temp_keyValuePair==NULL) return failure;


    if(hashTable1->hashtable_array[location_in_hashtable]==NULL) {
        // if the cell of hashtable is empty, means that there isn't any linked_list exist
        hashTable1->hashtable_array[location_in_hashtable]=createLinkedList(FreeKeyPair, PrintKeyPair, CopyKeyPair, CompareKeyPair);
        if(hashTable1->hashtable_array[location_in_hashtable]==NULL) return failure;
        appendNode(hashTable1->hashtable_array[location_in_hashtable], temp_keyValuePair);
        hashTable1->total_elements++;
    }
    else {
        appendNode(hashTable1->hashtable_array[location_in_hashtable], temp_keyValuePair);
        hashTable1->total_elements++;
    }
    return success;
};


Element lookupInHashTable(hashTable hashTable1, Element key){
    if(hashTable1==NULL || key == NULL) return NULL;
    // look up in the hash table - O(1) in average
    Element search_value_result = searchByKeyInList(hashTable1->hashtable_array[hashTable1->transformIntoNumber(key)%(hashTable1->hash_number)], key);
        if(search_value_result!=NULL)
            return getValue((KeyValuePair)search_value_result);

    return NULL;
};

status removeFromHashTable(hashTable hashTable1, Element key) {
    // the function delete a node from the hashTable  - O(1) to find it average
    if (hashTable1 == NULL || key == NULL) return failure;
    int location_in_hashtable = hashTable1->transformIntoNumber(key)%(hashTable1->hash_number);
    if (deleteNode(hashTable1->hashtable_array[location_in_hashtable], key) == success) {
        hashTable1->total_elements--;
        return success;
    }
    return failure;
}
status displayHashElements(hashTable hashTable1){
    if(hashTable1==NULL) return failure;
    for (int i = 0; i < hashTable1->hash_number; i++) {
        printf("print the cell number %d within the hashtable\n", i+1);
        displayList(hashTable1->hashtable_array[i]);
    }
    return success;
}

// help function which return the amount to total elements within the hasthTable
int totalElements(hashTable hashTable1){
    if(hashTable1==NULL) return 0;
    return hashTable1->total_elements;
}